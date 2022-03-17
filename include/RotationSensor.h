#ifndef ROTATIONSENSOR_H
#define ROTATIONSENSOR_H

#include <Arduino.h>

class RotationSensor {
private:
    byte pin;

    bool expected;
    bool value;

    int threshold;

public:
    RotationSensor(byte pin, int threshold = 2000);
    void init();

    bool readValue();
    void resetValue();
    bool getValue();

    void expect(bool expect);
    bool isExpected();

    byte getPin();
};

#endif
