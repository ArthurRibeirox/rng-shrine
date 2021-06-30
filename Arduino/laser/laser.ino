#include <SoftwareSerial.h>

const int bluetoothRXPin = 12;
const int bluetoothTXPin = 13;

const int bodyRedPin = 11;
const int bodyGreenPin = 10;
const int bodyBluePin = 9;
const int headRedPin = 3;
const int headGreenPin = 5;
const int headBluePin = 6;

const int MovementSensorPin = A0;

SoftwareSerial bluetooth(bluetoothRXPin, bluetoothTXPin);

void setup() {
    Serial.begin(9600); // setup serial
    pinMode(MovementSensorPin, INPUT);
  
    pinMode(bodyRedPin, OUTPUT);
    pinMode(bodyGreenPin, OUTPUT);
    pinMode(bodyBluePin, OUTPUT);
    analogWrite(bodyRedPin, 255);
    analogWrite(bodyGreenPin, 255);
    analogWrite(bodyBluePin, 255);
    
    pinMode(headRedPin, OUTPUT);
    pinMode(headGreenPin, OUTPUT);
    pinMode(headBluePin, OUTPUT);
    analogWrite(headRedPin, 255);
    analogWrite(headGreenPin, 255);
    analogWrite(headBluePin, 255);
    
    bluetooth.begin(9600);
    bluetooth.print("$");
    bluetooth.print("$");
    bluetooth.print("$");
}


long lastMillis;

void loop() {
    if (bluetooth.available()) {
        bluetooth.println("Command read: " + bluetooth.readStringUntil('\n'));
    }

    if (lastMillis + 100 < millis())
    {
        lastMillis = millis();

        Serial.println(analogRead(MovementSensorPin));
    }
} 
