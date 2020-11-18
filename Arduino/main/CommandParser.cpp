#include "CommandParser.h"

CommandParser::CommandParser(SoftwareSerial *bluetoothSerial, LightController** controllers)
{
    bluetooth = bluetoothSerial;
    bluetooth->begin(9600);
    bluetooth->print("$");

    lightControllers = controllers;
}

void CommandParser::TryParseCommands()
{
    if (bluetooth->available()) {
        int commandCode = ParseCommandCode();
        if (commandCode == -1) return;

        if (!FlushSeparator()) return;

        LightController* targetLight = GetTargetLight();
        if (targetLight == nullptr) return;

        int flushed = FlushSeparator();
        if (flushed == 0) return;

        commandArgumentsCount = 0;
        if (flushed == 1)
        {
            FillCommandArguments();
        }

        ((CommandParser*)this->*(commands[commandCode]))(targetLight);
    }
}

int CommandParser::ParseCommandCode()
{
    int commandCode = bluetooth->parseInt();

    if (commandCode <= 0 || commandCode > COMMANDS_COUNT)
    {
        ReportBug("Invalid command code: " + String(commandCode));
        return -1;
    }

    return commandCode - 1;
}

LightController* CommandParser::GetTargetLight()
{
    int lightIndex = bluetooth->parseInt();

    if (lightIndex <= 0 || lightIndex > LIGHTS_COUNT)
    {
        ReportBug("Invalid target lights controller: " + String(lightIndex));
        return nullptr;
    }

    return lightControllers[lightIndex];
}

bool CommandParser::FillCommandArguments()
{
    int flushed;
    
    for (int i = 0; i < MAX_COMMAND_ARGUMENTS; i++)
    {
        commandArguments[i] = bluetooth->parseInt();
        
        flushed = FlushSeparator();
        if (flushed == 0) return false;
        if (flushed == 2) return true;
    }

    flushed = FlushSeparator();
    if (flushed == 2) return true;
    if (flushed == 1)
        ReportBug("Command arguments exceeded max allowed.");
    
    return false;
}

void CommandParser::ClearLightAnimationStepsCommand(LightController* lightController)
{
}

void CommandParser::SetLightColorCommand(LightController* lightController)
{
}

void CommandParser::LerpLightColorCommand(LightController* lightController)
{
}

// void SetRGBOperation()
// {
//   analogWrite(redPin, bluetooth->parseInt());
//   FlushSeparator(',');
//   analogWrite(greenPin, bluetooth->parseInt());
//   FlushSeparator(',');
//   analogWrite(bluePin, bluetooth->parseInt());
//   FlushSeparator('\n');
// }

// void GetTargetLedStrip()
// {
//     // TODO
//     bluetooth->parseInt(); // This should be the led id
//     FlushSeparator('|');
// }

int CommandParser::FlushSeparator(char separator = ARGUMENT_SEPARATOR)
{
    int foundSeparator = bluetooth->read();

    if (foundSeparator == COMMAND_SEPARATOR) return 2;

    if (foundSeparator != separator)
    {
        ReportBug("Wrong separator! Expected: " + String(separator) + ", got: " + String(foundSeparator));
        return 0;
    }

    return 1;
}

void CommandParser::ReportBug(String message)
{
    bluetooth->println(
        "[Error] " +
        message +
        ", Remaining command: " +
        bluetooth->readStringUntil('\n')
    );
}