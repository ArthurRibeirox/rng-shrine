#ifndef CommandParser_h
#define CommandParser_h

#include "LightController.h"
#include <SoftwareSerial.h>

#define COMMANDS_COUNT 3
#define LIGHTS_COUNT 2
#define MAX_COMMAND_ARGUMENTS 10

#define ARGUMENT_SEPARATOR ','
#define COMMAND_SEPARATOR '\n'

class CommandParser {

public:
    CommandParser(SoftwareSerial *bluetoothSerial, LightController** controllers);

    void TryParseCommands();

private:
    int ParseCommandCode();
    LightController* GetTargetLight();
    bool FillCommandArguments();

    int FlushSeparator(char separator = ARGUMENT_SEPARATOR); // 0 - fail, 1 - matches, 2 - command separator
    void ReportBug(String message);

    int commandArguments[MAX_COMMAND_ARGUMENTS];
    int commandArgumentsCount;
    
    void ClearLightAnimationStepsCommand(LightController* lightController);
    void SetLightColorCommand(LightController* lightController);
    void LerpLightColorCommand(LightController* lightController);

    void (CommandParser::*commands[COMMANDS_COUNT])(LightController*) = { &ClearLightAnimationStepsCommand, &SetLightColorCommand, &LerpLightColorCommand } ;

    SoftwareSerial* bluetooth;
    LightController** lightControllers;
};

#endif
