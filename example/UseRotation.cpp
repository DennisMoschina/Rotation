#include <Arduino.h>
#include <Rotation.h>

byte sensorPins[] = {2, 3};
RotationSensor sensors[] = {RotationSensor(sensorPins[0]), RotationSensor(sensorPins[1])};

Rotation rotation(&sensors[0], &sensors[1]);

class MyRotationCallback: public RotationCallback {
public:
    void didTurn(RotationData turnData) {
        Serial.print("turns: ");
        Serial.println(turnData.turns);
        Serial.print("rpm: ");
        Serial.println(turnData.rpm);
    }
};

void setup() {
    Serial.begin(9600);
  
    rotation.setCallback(new MyRotationCallback());
}

void loop() {}
