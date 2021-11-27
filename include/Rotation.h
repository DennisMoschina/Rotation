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
    RotationSensor sensor1;
    RotationSensor sensor2;

    void (*didTurnCallback)(void*);

    unsigned long firstTime;
    unsigned long nextTime;

    RotationData rotationData;

    void didTurn();

public:
    Rotation(byte sensor1Pin, byte sensor2Pin);
    void init();

    void sensor1didRegister();
    void sensor2didRegister();

    void setCallback(void (*didTurnCallbackUsr)(void*)) {
        didTurnCallback = didTurnCallbackUsr;
    }

    RotationData getData();
    void reset();
};

#endif
