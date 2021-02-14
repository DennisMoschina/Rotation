#include <RotationSensor.h>

RotationSensor::RotationSensor(byte pin) {
  this->pin = pin;
  init();
}

void RotationSensor::init() {
  expected = true;
  value = false;
}

byte RotationSensor::getPin() {
  return pin;
}
