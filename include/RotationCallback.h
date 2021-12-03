#ifndef _ROTATION_CALLBACK_H
#define _ROTATION_CALLBACK_H

#include "RotationData.h"

class RotationCallback {
public:
    virtual void didTurn(RotationData data) = 0;
};

#endif