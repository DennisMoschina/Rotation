#ifndef _ROTATION_DATA_H
#define _ROTATION_DATA_H

typedef struct RotationData {
    unsigned int turns;
    unsigned int rpm;

    void clear() {
        turns = 0;
        rpm = 0;
    }
};

#endif