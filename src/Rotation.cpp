#include <Rotation.h>
#include <RotationSensor.h>


Rotation *pointerToClassRT;

static void outsideSensor1didRegister() {
  pointerToClassRT->sensor1didRegister();
}

static void outsideSensor2didRegister() {
  pointerToClassRT->sensor2didRegister();
}


Rotation::Rotation(byte sensor1Pin, byte sensor2Pin):
  sensor1(RotationSensor(sensor1Pin)),
  sensor2(RotationSensor(sensor2Pin)) {

  init();
}

void Rotation::init() {
  attachInterrupt(digitalPinToInterrupt(sensor1.getPin()), outsideSensor1didRegister, HIGH);
  attachInterrupt(digitalPinToInterrupt(sensor2.getPin()), outsideSensor2didRegister, HIGH);

  firstTime = 0;
  nextTime = 0;

  rotationData.rpm = 0;
  rotationData.turns = 0;
}

void Rotation::sensor1didRegister() {
  if (sensor1.expected) {
    if (sensor2.value) {
      didTurn();
      sensor2.value = false;
    } else {
      sensor1.value = true;
    }
    sensor2.expected = true;
    sensor1.expected = false;
  }
}

void Rotation::sensor2didRegister() {
  if (sensor2.expected) {
    if (sensor1.value) {
      didTurn();
      sensor1.value = false;
    } else {
      sensor2.value = true;
    }
    sensor1.expected = true;
    sensor2.expected = false;
  }
}

void Rotation::didTurn() {
  rotationData.turns += 1;

  firstTime = nextTime;
  nextTime = millis();

  unsigned long diff = (nextTime - firstTime);

  if (diff == 0) {
    rotationData.rpm = 0;
  } else {
    rotationData.rpm = 60000 / diff;
  }

  didTurnCallback();
}

data Rotation::getData() {
  return rotationData;
}

void Rotation::reset() {
  sensor1.expected = true;
  sensor2.expected = true;

  sensor1.value = false;
  sensor2.value = false;

  rotationData.clear();
}
