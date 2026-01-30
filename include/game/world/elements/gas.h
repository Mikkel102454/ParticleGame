//
// Created by mikkel on 1/27/2026.
//

#ifndef UNA_GAS_H
#define UNA_GAS_H
#include "game/world/element.h"

typedef struct Gas : Element {
    virtual int GetDispersionRate() const = 0;
} Gas;

#endif //UNA_GAS_H