#ifndef MY_ROTATION_H
#define MY_ROTATION_H

#include <Arduino.h>
#include "RotationSensor.h"
#include "RotationData.h"
#include "RotationCallback.h"

class Rotation {
private:
    RotationSensor** sensors;
    size_t sensorCount;

    RotationCallback* callback = nullptr;

    unsigned long firstTime;
    unsigned long nextTime;

    RotationData rotationData;

    void didTurn();

public:
    Rotation(RotationSensor** sensors, size_t sensorCount);
    void begin();

    void sensorDidRegister(size_t sensor);

    void setCallback(RotationCallback* callback);

    void handle();

    RotationData getData();
    void reset();
};

#endif
