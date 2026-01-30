#include "game/world/elements/solid/movable/sand.h"

#include <iostream>
#include <ostream>
#include <string>

#include "game/utils/random.h"
#include "game/world/elements/liquid/water.h"

void Sand::Step() {
    if (!world->IsInsideBounds(x, y + 1)) {
        return;
    }

    bool down      = world->GetElement(x, y + 1) == nullptr || world->GetElement(x, y + 1)->GetMass() < GetMass();
    bool downLeft  = world->GetElement(x - 1, y + 1) == nullptr || world->GetElement(x - 1, y + 1)->GetMass() < GetMass();
    bool downRight = world->GetElement(x + 1, y + 1) == nullptr || world->GetElement(x + 1, y + 1)->GetMass() < GetMass();


    if (down) {
        vY += world->gravity * GetFrameTime();
    }
    else if (downLeft || downRight) {
        // Always falling if sliding diagonally
        vY = world->gravity * GetFrameTime();

        if (downLeft && downRight) {
            vX = (random_val_int(0, 1)) ? -1.0f : 1.0f;
        }
        else if (downLeft) {
            vX = -1.0f;
        }
        else {
            vX = 1.0f;
        }
    } else {
        isActive = false;
    }


    std::vector<int> desiredPath = world->ComputeTraverse(x, y, vX, vY);

    int indexToTravel = -1;
    if (!desiredPath.empty()) {
        world->ActivateArea(x, y);

        for (int i = 0; i < desiredPath.size(); i++) {
            int x;
            int y;
            world->ConvertIndexToCoord(desiredPath[i], x, y);

            if (world->IsInsideBounds(x, y) && (world->GetElement(x, y) == nullptr || world->GetElement(x, y)->GetMass() < GetMass())) {
                indexToTravel++;
                world->ActivateArea(x, y);
            }
        }

        if (indexToTravel != -1) {
            int x;
            int y;
            world->ConvertIndexToCoord(desiredPath[indexToTravel], x, y);

            world->SwapElement(this->x, this->y, x, y);
        } else {
            vY = 0;
        }
    } else {
        vY = 0;
    }
    vX = 0;
}