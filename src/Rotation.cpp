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
    if (sensor1.isExpected()) {
        if (sensor2.isExpected()) {
            didTurn();
            sensor2.setValue(false);
        } else {
            sensor1.setValue(true);
        }
        sensor2.expect(true);
        sensor1.expect(false);
    }
}

void Rotation::sensor2didRegister() {
    if (sensor2.isExpected()) {
        if (sensor1.isExpected()) {
            didTurn();
            sensor1.setValue(false);
        } else {
            sensor2.setValue(true);
        }
        sensor2.expect(true);
        sensor1.expect(false);
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

    didTurnCallback(NULL);
}

RotationData Rotation::getData() {
    return rotationData;
}

void Rotation::reset() {
    sensor1.expect(true);
    sensor2.expect(true);

    sensor1.setValue(false);
    sensor2.setValue(false);

    rotationData.clear();
}
