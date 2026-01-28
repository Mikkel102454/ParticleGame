#include "game/world/elements/solid/movable/sand.h"

#include <iostream>
#include <ostream>

#include "game/utils/random.h"
#include "game/world/elements/liquid/water.h"

void Sand::Step() {
    if (!world->IsInsideBounds(x, y + 1)) {
        return;
    }

    if (world->GetElement(x, y + 1) == nullptr) {
        vY += world->gravity * GetFrameTime();
    }

    int desiredPath[0];
    world->ComputeTraverse(x, y, vX, vY, *desiredPath);

    if (world->GetElement(x, y + 1) == nullptr) {
        vY += world->gravity * GetFrameTime();

        int pixelsToMove = std::ceil(vY);
        for (int i = 0; i < pixelsToMove; i++) {
            if (!world->IsInsideBounds(x, y + 1)) break;

            if (world->GetElement(x, y + 1) == nullptr) {
                world->SwapElement(x, y, x, y + 1);
            };
        }
    }
    else {
        int direction = 1;
        direction = random_val_int(0, 1) ? direction : -direction;
        if (!goDiagonal(direction)) {
            goDiagonal(-direction);
        }
    }

    //calculate physics
}

bool Sand::goDiagonal(int direction) {
    if (!world->IsInsideBounds(x + direction, y + 1)) return false;
    if (world->GetElement(x + direction, y + 1) == nullptr) { //|| dynamic_cast<Water*>(world->Get_Element(x, y + 1)) != nullptr) {
        world->SwapElement(x, y, x + direction, y + 1);
        return true;
    }
    return false;
}