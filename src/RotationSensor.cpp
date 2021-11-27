#include <RotationSensor.h>

RotationSensor::RotationSensor(byte pin) {
    this->pin = pin;
    init();
}

void RotationSensor::init() {
    expected = true;
    value = false;
}

void RotationSensor::setValue(bool value) {
    this->value = value;
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
