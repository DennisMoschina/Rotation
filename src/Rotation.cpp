#include <Rotation.h>
#include <RotationSensor.h>

void handleRotation(void* rotation) {
    for (;;) ((Rotation*) rotation)->handle();
}

Rotation::Rotation(RotationSensor* sensor1, RotationSensor* sensor2) {
    this->sensor1 = sensor1;
    this->sensor2 = sensor2;
}

void Rotation::begin() {
    xTaskCreate(handleRotation, "handleRotation", 2000, this, 0, NULL);

    firstTime = 0;
    nextTime = 0;

    rotationData.rpm = 0;
    rotationData.turns = 0;
}

void Rotation::sensor1didRegister() {
    if (this->sensor1->isExpected()) {
        this->sensor1->expect(false);
        this->sensor2->expect(true);
        if (sensor2->getValue()) {
            this->didTurn();
        }
    }
}

void Rotation::sensor2didRegister() {
    if (this->sensor2->isExpected()) {
        this->sensor2->expect(false);
        this->sensor1->expect(true);
        if (sensor1->getValue()) {
            this->didTurn();
        }
    }
}

void Rotation::didTurn() {
    rotationData.turns += 1;

    firstTime = nextTime;
    nextTime = millis();

    this->sensor1->resetValue();
    this->sensor2->resetValue();

    unsigned long diff = (nextTime - firstTime);

    if (diff == 0) {
        rotationData.rpm = 0;
    } else {
        rotationData.rpm = 60000 / diff;
    }

    didTurnCallback();
}

void Rotation::handle() {
    if (!sensor1->getValue()) {
        if (sensor1->readValue()) this->sensor1didRegister();
    }
    if (!sensor2->getValue()) {
        if (sensor2->readValue()) this->sensor2didRegister();
    }
}

RotationData Rotation::getData() {
    return rotationData;
}

void Rotation::reset() {
    sensor1->expect(true);
    sensor2->expect(true);

    sensor1->resetValue();
    sensor2->resetValue();

    rotationData.clear();
}
