#ifndef CommandParser_h
#define CommandParser_h

#include "LightController.h"
#include <SoftwareSerial.h>

#define COMMANDS_COUNT 3
#define LIGHTS_COUNT 2
#define MAX_COMMAND_ARGUMENTS 10

#define ARGUMENT_SEPARATOR ','
#define COMMAND_SEPARATOR1 '\n'
#define COMMAND_SEPARATOR2 '\r'

class CommandParser {

public:
    CommandParser(SoftwareSerial *bluetoothSerial, LightController** controllers);

    void TryParseCommands(long millis);

private:
    bool FillCommandArguments();
    int ParseCommandCode();
    LightController* GetTargetLight();

    int CheckSeparator(char commandChar); // 0 - fail, 1 - matches, 2 - command separator
    void ReportBug(String message);

    String currentCommand;
    int commandArguments[MAX_COMMAND_ARGUMENTS];
    int commandArgumentsCount;
    
    void ClearLightAnimationStepsCommand(LightController* lightController, long millis);
    void SetLightColorCommand(LightController* lightController, long millis);
    void LerpLightColorCommand(LightController* lightController, long millis);

    void (CommandParser::*commands[COMMANDS_COUNT])(LightController*, long) = {&ClearLightAnimationStepsCommand, &SetLightColorCommand, &LerpLightColorCommand} ;

    SoftwareSerial* bluetooth;
    LightController** lightControllers;
};

#endif
