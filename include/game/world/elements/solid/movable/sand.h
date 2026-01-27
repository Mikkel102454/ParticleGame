//
// Created by mikkel on 1/27/2026.
//

#ifndef UNA_SAND_H
#define UNA_SAND_H
#include "raylib.h"
#include "game/world/elements/solid/movable.h"

struct Sand : Movable {
    Color GetColor() const override{
        return ORANGE;
    }

    void ReceiveHeat() override{
        return;
    }

    void Step() override;
    bool goDiagonal(int direction);
};

#endif //UNA_SAND_H