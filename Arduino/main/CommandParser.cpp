#include "CommandParser.h"
#include "LightAnimationStep.h"
#include "LerpLightAnimationStep.h"
#include "FastLED.h"

CommandParser::CommandParser(SoftwareSerial *bluetoothSerial, LightController** controllers)
{
    bluetooth = bluetoothSerial;
    bluetooth->begin(9600);
    bluetooth->print("$");
    bluetooth->print("$");
    bluetooth->print("$");

    lightControllers = controllers;
}

void CommandParser::TryParseCommands(long millis)
{
    if (bluetooth->available()) {
        currentCommand = bluetooth->readStringUntil('\n');
        Serial.println("Command read: " + currentCommand);

        if (!FillCommandArguments())
        {
            return;
        }

        Serial.print("Arguments found: ");
        for(int i = 0; i < commandArgumentsCount; i++)
        {
            Serial.print(String(commandArguments[i]) + " | ");
        }
        Serial.print("\n");

        int commandCode = ParseCommandCode();
        if (commandCode == -1) return;

        LightController* targetLight = GetTargetLight();
        if (targetLight == nullptr) return;

        ((CommandParser*)this->*(commands[commandCode]))(targetLight, millis);
    }
}

int CommandParser::ParseCommandCode()
{
    int commandCode = commandArguments[0];

    if (commandCode <= 0 || commandCode > COMMANDS_COUNT)
    {
        ReportBug("Invalid command code: " + String(commandCode));
        return -1;
    }

    return commandCode - 1;
}

LightController* CommandParser::GetTargetLight()
{
    int lightIndex = commandArguments[1];

    if (lightIndex <= 0 || lightIndex > LIGHTS_COUNT)
    {
        ReportBug("Invalid target lights controller: " + String(lightIndex));
        return nullptr;
    }

    return lightControllers[lightIndex-1];
}

bool CommandParser::FillCommandArguments()
{
    int separatorCheck;
    commandArgumentsCount = 0;

    for (int i = 0; i < currentCommand.length(); i++)
    {
        if (commandArgumentsCount >= MAX_COMMAND_ARGUMENTS)
        {
            ReportBug("Command arguments exceeded max allowed.");
            return false;
        }

        int numberStartIndex = i;
        while(isdigit(currentCommand.charAt(i))) i++;

        if (numberStartIndex == i)
        {
            ReportBug("Expected command argument!");
            return;
        }

        String sub = currentCommand.substring(numberStartIndex, i);
        int parsed = sub.toInt();

        commandArguments[commandArgumentsCount] = currentCommand.substring(numberStartIndex, i).toInt();
        commandArgumentsCount++;
        
        separatorCheck = CheckSeparator(currentCommand.charAt(i));
        if (separatorCheck == 0) return false;
        if (separatorCheck == 2) return true;
    }
    
    Serial.println("What the flying");
    return false;
}

void CommandParser::ClearLightAnimationStepsCommand(LightController* lightController, long millis)
{
    lightController->ClearAnimationSteps();
}

void CommandParser::SetLightColorCommand(LightController* lightController, long millis)
{
    if (commandArgumentsCount != 6)
    {
        ReportBug("Command arguments differ from command called: SetLightColorCommand");
        return;
    }

    CRGB startColor = CRGB(commandArguments[2], commandArguments[3], commandArguments[4]);

    lightController->AddAnimationStep(new LightAnimationStep(startColor, commandArguments[5]), millis);
}

void CommandParser::LerpLightColorCommand(LightController* lightController, long millis)
{
    if (commandArgumentsCount != 9 && commandArgumentsCount != 10)
    {
        ReportBug("Command arguments differ from command called: SetLightColorCommand");
        return;
    }

    CRGB startColor = CRGB(commandArguments[2], commandArguments[3], commandArguments[4]);
    CRGB targetColor = CRGB(commandArguments[5], commandArguments[6], commandArguments[7]);
    bool loop = commandArgumentsCount == 10 ? commandArguments[9] : false;

    lightController->AddAnimationStep(new LerpLightAnimationStep(startColor, targetColor, commandArguments[8], loop), millis);
}

int CommandParser::CheckSeparator(char commandChar)
{
    if (commandChar == COMMAND_SEPARATOR1 || commandChar == COMMAND_SEPARATOR2) return 2;

    if (commandChar != ARGUMENT_SEPARATOR)
    {
        ReportBug("Expected command argument separator, got: `" + String(commandChar) + "` ");
        return 0;
    }

    return 1;
}

void CommandParser::ReportBug(String message)
{
    String str = "[Error] " + message + ", command: " + currentCommand;

    bluetooth->println(str);
    Serial.println(str);
}