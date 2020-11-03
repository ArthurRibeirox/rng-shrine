#include <SoftwareSerial.h>

const int bluetoothRXPin = 2;
const int bluetoothTXPin = 3;

const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

SoftwareSerial bluetooth(bluetoothRXPin, bluetoothTXPin);

void SetRGBOperation()
{
  analogWrite(redPin, bluetooth.parseInt());
  FlushSeparator(',');
  analogWrite(greenPin, bluetooth.parseInt());
  FlushSeparator(',');
  analogWrite(bluePin, bluetooth.parseInt());
  FlushSeparator('\n');
}

void GetTargetLedStrip()
{
  // TODO
  bluetooth.parseInt(); // This should be the led id
  FlushSeparator('|');
}

void FlushSeparator(char separator)
{
  int foundSeparator = bluetooth.read(); // Discard separator '|'
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
  if (bluetooth.available()) {
//    ReportBug(bluetooth.readStringUntil('\n'));
    
    int operationCode = bluetooth.parseInt();

    if(operationCode == 0) {
      FlushSeparator('|');
      GetTargetLedStrip();
      SetRGBOperation();
    }
  }
}



void SetupLED() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
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
  SetupLED();
  SetupBluetooth();
}
