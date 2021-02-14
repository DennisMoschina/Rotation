#ifndef ROTATIONSENSOR_H
#define ROTATIONSENSOR_H

#include <Arduino.h>

class RotationSensor {
  private:
    byte pin;

  public:
    RotationSensor(byte pin);
    void init();

    bool expected;
    bool value;

    byte getPin();
};

#endif
