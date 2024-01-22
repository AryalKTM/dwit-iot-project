#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11);

const int redLED = 13;
const int greenLED = 12;
const int relayPIN = 9;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(relayPIN, OUTPUT);
  
  digitalWrite(greenLED, HIGH);
  digitalWrite(relayPIN, LOW);
}

void loop() {
  if (bluetooth.available() > 0) {
    char receivedData = bluetooth.read();
    Serial.print("Received data: ");
    Serial.println(receivedData);

    if (receivedData == '1') {
      unlockDoor();
      delay(15000);
      lockDoor();
    } else {
      lockDoor();
    }

    while (bluetooth.available() > 0) {
      bluetooth.read();
    }
  }
}

void lockDoor() {
  digitalWrite(relayPIN, HIGH);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, HIGH);
  Serial.println("DOOR LOCKED");
  bluetooth.print("DOOR LOCKED");
}

void unlockDoor() {
  digitalWrite(relayPIN, LOW);
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
  Serial.println("DOOR UNLOCKED");
  bluetooth.print("DOOR UNLOCKED");
}

