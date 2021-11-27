#ifndef ROTATIONSENSOR_H
#define ROTATIONSENSOR_H

#include <Arduino.h>

class RotationSensor {
private:
    byte pin;

    bool expected;
    bool value;

public:
    RotationSensor(byte pin);
    void init();

    void setValue(bool value);
    void expect(bool expect);

    bool getValue();
    bool isExpected();

    byte getPin();
};

#endif
