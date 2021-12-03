#ifndef MY_ROTATION_H
#define MY_ROTATION_H

#include <Arduino.h>
#include "RotationSensor.h"
#include "RotationData.h"
#include "RotationCallback.h"


class Rotation {
private:
    RotationSensor* sensor1;
    RotationSensor* sensor2;

    RotationCallback* callback;

    unsigned long firstTime;
    unsigned long nextTime;

    RotationData rotationData;

    void didTurn();

public:
    Rotation(RotationSensor* sensor1, RotationSensor* sensor2);
    void begin();

    void sensor1didRegister();
    void sensor2didRegister();

    void setCallback(RotationCallback* callback);

    void handle();

    RotationData getData();
    void reset();
};

#endif
