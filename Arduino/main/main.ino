#include <SoftwareSerial.h>

const int bluetoothRXPin = 2;
const int bluetoothTXPin = 3;

const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

SoftwareSerial bluetooth(bluetoothRXPin, bluetoothTXPin);

void SetRGBOperation()
{
  bluetooth.read(); // Discard separator '|'
  analogWrite(redPin, bluetooth.parseInt());
  bluetooth.read(); // Discard separator ','
  analogWrite(greenPin, bluetooth.parseInt());
  bluetooth.read(); // Discard separator ','
  analogWrite(bluePin, bluetooth.parseInt());
}

void loop() {
  if (bluetooth.available()) {
    int operationCode = bluetooth.parseInt();

    if(operationCode == 1) {
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
