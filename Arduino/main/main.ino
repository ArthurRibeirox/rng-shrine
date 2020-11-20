#include <SoftwareSerial.h>
#include "FastLED.h"
#include "LightController.h"
#include "CommandParser.h"
#include "LerpLightAnimationStep.h"

const int bluetoothRXPin = 2;
const int bluetoothTXPin = 3;

const int bodyRedPin = 11;
const int bodyGreenPin = 10;
const int bodyBluePin = 9;

const int MovementSensorPin = 13;

SoftwareSerial bluetooth(bluetoothRXPin, bluetoothTXPin);

LightController* lightControllers[2];
CommandParser* commandParser;

void loop() {
    commandParser->TryParseCommands(millis());
    lightControllers[0]->Update(millis());
}

void setup() {
    Serial.begin(9600);

    // pinMode(MovementSensorPin, INPUT);

    lightControllers[0] = new LightController(bodyRedPin, bodyGreenPin, bodyBluePin);
    
    commandParser = new CommandParser(&bluetooth, lightControllers);
}




//  int movementOccurred = digitalRead(MovementSensorPin);
//
//  if(movementOccurred == HIGH)
//  {
    // CHSV hsv(hue++, 255, 100);
  //  CHSV hsv( random8(), random8(), random8() );  //pick random HSV
    // CRGB rgb;
    // hsv2rgb_rainbow(hsv, rgb);
    // SetLED(rgb);
    // delay(10);
//  }
//  else
//  {
//    SetLED(CRGB(0,0,0));
//  }