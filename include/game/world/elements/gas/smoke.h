//
// Created by mikkel on 1/27/2026.
//

#ifndef UNA_SMOKE_H
#define UNA_SMOKE_H
#include "raylib.h"
#include "game/world/elements/gas.h"

typedef struct Smoke : Gas {
    Color GetColor() const override{
        return GRAY;
    }
    float GetMass() const override{
        return 1.0f;
    }

    void ReceiveHeat() override{
        return;
    }

    int GetDispersionRate() const override{
        return 5;
    }

    void Step() override;
} Smoke;

#endif //UNA_SMOKE_H