//
// Created by mikkel on 1/27/2026.
//

#ifndef UNA_SAND_H
#define UNA_SAND_H
#include "raylib.h"
#include "game/world/elements/solid/movable.h"

typedef struct Sand : Movable {
    Color GetColor() const override{
        return ORANGE;
    }
    float GetMass() const override{
        return 10.0f;
    }

    void ReceiveHeat() override{
        return;
    }

    void Step() override;
    bool goDiagonal(int direction);
} Sand;

#endif //UNA_SAND_H