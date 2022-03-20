#include <Rotation.h>
#include <RotationSensor.h>

void handleRotation(void* rotation) {
    for (;;) ((Rotation*) rotation)->handle();
}

void handleSingleSensorRotation(void* rotation) {
    for (;;) ((Rotation*) rotation)->handleSingleSensor();
}

Rotation::Rotation(RotationSensor** sensors, size_t sensorCount) {
    this->sensors = sensors;
    this->sensorCount = sensorCount;

    this->setFrequency(1000);
}

void Rotation::begin() {
    xTaskCreate(this->sensorCount > 1 ? handleRotation : handleSingleSensorRotation,
                "handleRotation",
                2000,
                this,
                3,
                NULL);

    firstTime = 0;
    nextTime = 0;

    rotationData.rpm = 0;
    rotationData.turns = 0;
}

void Rotation::setFrequency(uint16_t frequency) {
    this->delayTime = 1000 / frequency;
}

///warning: - currently only works in one direction
void Rotation::sensorDidRegister(size_t sensor) {
    this->sensors[sensor]->expect(false);
    this->sensors[(sensor + 1) % this->sensorCount]->expect(true);
    for (size_t i = 0; i < this->sensorCount; i++) {
        if (!this->sensors[i]->getValue()) return;
    }
    this->didTurn();
}

void Rotation::didTurn() {
    this->rotationData.turns++;

    this->firstTime = nextTime;
    this->nextTime = millis();

    for (size_t i = 0; i < this->sensorCount; i++) {
        this->sensors[i]->resetValue();
    }

    unsigned long diff = (nextTime - firstTime);

    if (diff == 0) {
        this->rotationData.rpm = 0;
    } else {
        this->rotationData.rpm = 60000 / diff;
    }

    if (this->callback != nullptr) this->callback->didTurn(this->rotationData);
}

void Rotation::setCallback(RotationCallback* callback) {
    this->callback = callback;
}

void Rotation::handleSingleSensor() {
    RotationSensor* sensor = this->sensors[0];
    if (sensor->readValue()) {
        if (sensor->isExpected()) {
            sensor->expect(false);
            this->didTurn();
        }
    } else {
        if (!sensor->isExpected()) {
            sensor->expect(true);
        }
    }
    delay(this->delayTime);
}

void Rotation::handle() {
    for (size_t i = 0; i < this->sensorCount; i++) {
        RotationSensor* sensor = this->sensors[i];
        if (sensor->isExpected()) {
            if (sensor->readValue()) {
                this->sensorDidRegister(i);
                return;
            }
        }
    }
    delay(this->delayTime);
}

RotationData Rotation::getData() {
    return rotationData;
}

void Rotation::reset() {
    for (size_t i = 0; i < this->sensorCount; i++) {
        RotationSensor* sensor = this->sensors[i];
        sensor->expect(true);
        sensor->resetValue();
    }

    rotationData.clear();
}
