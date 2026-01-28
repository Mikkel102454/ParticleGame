//
// Created by mikkel on 1/27/2026.
//

#ifndef UNA_WATER_H
#define UNA_WATER_H
#include "game/world/elements/liquid.h"

struct Water : Liquid {
    Color GetColor() const override{
        return BLUE;
    }

    void ReceiveHeat() override{
        return;
    }

    int GetDispersionRate() const override{
        return 5;
    }

    void Step() override;
};

#endif //UNA_WATER_H