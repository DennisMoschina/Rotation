#ifndef MY_ROTATION_H
#define MY_ROTATION_H

#include <Arduino.h>
#include <RotationSensor.h>

typedef struct RotationData {
    unsigned int turns;
    unsigned int rpm;

    void clear() {
        turns = 0;
        rpm = 0;
    }
};


class Rotation {
private:
    RotationSensor* sensor1;
    RotationSensor* sensor2;

    void (*didTurnCallback)();

    unsigned long firstTime;
    unsigned long nextTime;

    RotationData rotationData;

    void didTurn();

public:
    Rotation(RotationSensor* sensor1, RotationSensor* sensor2);
    void begin();

    void sensor1didRegister();
    void sensor2didRegister();

    void setCallback(void (*didTurnCallbackUsr)()) {
        didTurnCallback = didTurnCallbackUsr;
    }

    void handle();

    RotationData getData();
    void reset();
};

#endif
