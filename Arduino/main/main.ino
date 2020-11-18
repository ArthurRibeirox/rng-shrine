#include <SoftwareSerial.h>
#include "FastLED.h"
#include "LightController.h"
#include "CommandParser.h"
#include "LerpLightAnimationStep.h"

const int bluetoothRXPin = 2;
const int bluetoothTXPin = 3;
const int MovementSensorPin = 13;




SoftwareSerial bluetooth(bluetoothRXPin, bluetoothTXPin);
LightController* lightControllers[2];
CommandParser* commandParser;

void loop() {
    commandParser->TryParseCommands();
    lightControllers[0]->Update(millis());






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
  
}

void setup() {
    Serial.begin(9600);

    // pinMode(MovementSensorPin, INPUT);

    lightControllers[0] = new LightController(11, 10, 9);

    // lightControllers[0]->AddAnimationStep(new LightAnimationStep(CRGB::Blue, 1), millis());
    lightControllers[0]->AddAnimationStep(new LerpLightAnimationStep(CRGB::Blue, CRGB::Red, 500, true), millis());
    lightControllers[0]->AddAnimationStep(new LerpLightAnimationStep(CRGB::Red, CRGB::Blue, 10000, true), millis());

    commandParser = new CommandParser(&bluetooth, lightControllers);
}
