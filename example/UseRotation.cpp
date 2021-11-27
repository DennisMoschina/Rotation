#include <Arduino.h>
#include <Rotation.h>

byte sensorPins[] = {2, 3};

Rotation rotation(sensorPins[0], sensorPins[1]);

void didTurn() {
    RotationData turnData = rotation.getData();
  
    Serial.print("turns: ");
    Serial.println(turnData.turns);
    Serial.print("rpm: ");
    Serial.println(turnData.rpm);
}

void setup() {
    Serial.begin(9600);
  
    rotation.setCallback(didTurn);
}

void loop() {}
