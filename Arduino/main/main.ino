#include <SoftwareSerial.h>
#include "FastLED.h"
#include "LightController.h"
#include "LightAnimationStep.h"

const int bluetoothRXPin = 2;
const int bluetoothTXPin = 3;
const int MovementSensorPin = 13;

LightController* lightControllers[2];

uint8_t hue = 0;

SoftwareSerial bluetooth(bluetoothRXPin, bluetoothTXPin);

// void SetRGBOperation()
// {
//   analogWrite(redPin, bluetooth.parseInt());
//   FlushSeparator(',');
//   analogWrite(greenPin, bluetooth.parseInt());
//   FlushSeparator(',');
//   analogWrite(bluePin, bluetooth.parseInt());
//   FlushSeparator('\n');
// }

void GetTargetLedStrip()
{
  // TODO
  bluetooth.parseInt(); // This should be the led id
  FlushSeparator('|');
}

void FlushSeparator(char separator)
{
  int foundSeparator = bluetooth.read();
  if (foundSeparator != separator)
  {
    ReportBug(String("Wrong separator! Expected: " + String(separator) + ", got: " + String(foundSeparator)));
  }
}

void ReportBug(String message)
{
  bluetooth.println("[Error] " + message);
}

void loop() {
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
  
//  if (bluetooth.available()) {
////    ReportBug(bluetooth.readStringUntil('\n'));
//    
//    int operationCode = bluetooth.parseInt();
//
//    if(operationCode == 0) {
//      FlushSeparator('|');
//      GetTargetLedStrip();
//      SetRGBOperation();
//    }
//  }
}

void SetupBluetooth() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  bluetooth.print("$");
  bluetooth.print("$");
  bluetooth.print("$");
  delay(100);
}

void setup() {
  SetupBluetooth();

  pinMode(MovementSensorPin, INPUT);

  lightControllers[0] = new LightController(11, 10, 9);

  lightControllers[0]->AddAnimationStep(new LightAnimationStep(CRGB::Blue, 1), millis());
}
