#include <RotationSensor.h>

RotationSensor::RotationSensor(byte pin, int threshold) {
    this->pin = pin;
    this->threshold = threshold;
    init();
}

void RotationSensor::init() {
    expected = true;
    value = false;
}

bool RotationSensor::readValue() {
    boolean value = analogRead(this->pin) > this->threshold;
    this->value = value;
    return value;
}

void RotationSensor::resetValue() {
    this->value = false;
}

void RotationSensor::expect(bool expect) {
    this->expected = expect;
}

bool RotationSensor::getValue() {
    return this->value;
}

bool RotationSensor::isExpected() {
    return this->expected;
}

byte RotationSensor::getPin() {
    return this->pin;
}
