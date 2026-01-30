//
// Created by mikkel on 1/27/2026.
//

#ifndef UNA_WOOD_H
#define UNA_WOOD_H
#include "raylib.h"
#include "game/world/elements/solid/immovable.h"

struct Wood : Immovable {
    Color GetColor() const override{
        return BROWN;
    }
    float GetMass() const override{
        return 10.0f;
    }

    void ReceiveHeat() override{
        return;
    }

    void Step() override;
};

#endif //UNA_WOOD_H