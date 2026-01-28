//
// Created by mikkel on 1/27/2026.
//

#ifndef UNA_LIQUID_H
#define UNA_LIQUID_H
#include "game/world/element.h"

typedef struct Liquid : Element {
    virtual int GetDispersionRate() const = 0;
} Liquid;

#endif //UNA_LIQUID_H