#ifndef MY_ROTATION_H
#define MY_ROTATION_H

#include <Arduino.h>
#include <RotationSensor.h>

typedef struct {
  int turns;
  int rpm;

  void clear() {
    turns = 0;
    rpm = 0;
  }
}data;


class Rotation {
  private:
    RotationSensor sensor1;
    RotationSensor sensor2;

    void (*didTurnCallback)();

    unsigned long firstTime;
    unsigned long nextTime;

    data rotationData;

    void didTurn();


  public:
    Rotation(byte sensor1Pin, byte sensor2Pin);
    void init();

    void sensor1didRegister();
    void sensor2didRegister();

    void setCallback(void (*didTurnCallbackUsr)()) {
      didTurnCallback = didTurnCallbackUsr;
    }

    data getData();
    void reset();
};

#endif
