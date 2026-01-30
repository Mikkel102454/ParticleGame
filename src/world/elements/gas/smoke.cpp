#include "game/world/elements/gas/smoke.h"

#include "game/utils/random.h"

void Smoke::Step() {
    bool down      = world->IsInsideBounds(x, y - 1) && (world->GetElement(x, y - 1) == nullptr || world->GetElement(x, y - 1)->GetMass() < GetMass());
    bool downLeft  = world->IsInsideBounds(x - 1, y - 1) && (world->GetElement(x - 1, y - 1) == nullptr || world->GetElement(x - 1, y - 1)->GetMass() < GetMass());
    bool downRight = world->IsInsideBounds(x + 1, y - 1) && (world->GetElement(x + 1, y - 1) == nullptr || world->GetElement(x + 1, y - 1)->GetMass() < GetMass());
    bool left      = world->IsInsideBounds(x - 1, y) && world->GetElement(x - 1, y) == nullptr;
    bool right     = world->IsInsideBounds(x + 1, y) &&world->GetElement(x + 1, y) == nullptr;


    if (down) {
        vY -= world->gravity * GetFrameTime();
    }
    else if (downLeft || downRight) {
        // Always falling if sliding diagonally
        vY = -5;

        if (downLeft && downRight) {
            vX = (random_val_int(0, 1)) ? -5.0f : 5.0f;
        }
        else if (downLeft) {
            vX = -5.0f;
        }
        else {
            vX = 5.0f;
        }
    }
    else if (left || right) {
        if (left && right) {
            vX = (random_val_int(0, 1)) ? -static_cast<float>(GetDispersionRate()) : static_cast<float>(GetDispersionRate());
        }
        else if (left) {
            vX = -static_cast<float>(GetDispersionRate());
        }
        else {
            vX = static_cast<float>(GetDispersionRate());
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