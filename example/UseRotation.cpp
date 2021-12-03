#include <Arduino.h>
#include <Rotation.h>

byte sensorPins[] = {2, 3};
RotationSensor sensors[] = {RotationSensor(sensorPins[0]), RotationSensor(sensorPins[1])};

Rotation rotation(&sensors[0], &sensors[1]);

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
