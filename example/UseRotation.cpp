#include <Arduino.h>
#include <Rotation.h>

byte sensorPins[] = {34, 35};
RotationSensor* sensors[] = {new RotationSensor(sensorPins[0]), new RotationSensor(sensorPins[1])};

Rotation rotation(sensors, 2);

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
    rotation.begin();
}

void loop() {
    delay(100);
}
