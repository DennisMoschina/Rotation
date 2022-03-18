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

    unsigned long delayTime;

    unsigned long firstTime;
    unsigned long nextTime;

    RotationData rotationData;

    void didTurn();

public:
    Rotation(RotationSensor** sensors, size_t sensorCount);
    void begin();

    /**
     * @brief Set the Frequency in which the manager should check the sensors.
     * @param frequency the frequency for checking the sensors. The maximum frequency is 1000Hz
     */
    void setFrequency(uint16_t frequency);

    void sensorDidRegister(size_t sensor);

    void setCallback(RotationCallback* callback);

    void handle();
    void handleSingleSensor();

    RotationData getData();
    void reset();
};

#endif
