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

    if (world->GetElement(x, y + 1) == nullptr) {
        vX += world->gravity * GetFrameTime();
    }

    std::vector<int> desiredPath = world->ComputeTraverse(x, y, vX, vY);

    int indexToTravel = -1;
    if (!desiredPath.empty()) {
        for (int i = 0; i < desiredPath.size(); i++) {
            int x;
            int y;
            world->ConvertIndexToCoord(i, x, y);

            if (!world->IsInsideBounds(x, y)) break;
            if (world->GetElement(x, y) != nullptr) break;

            indexToTravel = i;
        }

        if (indexToTravel != -1) {
            int x;
            int y;
            world->ConvertIndexToCoord(indexToTravel, x, y);

            world->SwapElement(this->x, this->y, x, y);
        } else {
            vX = 0;
        }
    //     if (world->GetElement(desiredPath[0]) == nullptr) {
    //         for (int i = 0; i < desiredPath.size(); i++) {
    //             if (i + 1 < desiredPath.size()) {
    //                 int x = 0;
    //                 int y = 0;
    //                 world->ConvertIndexToCoord(desiredPath[i + 1], x, y);
    //                 if (!world->IsInsideBounds(x, y) || world->GetElement(x, y) != nullptr) {
    //
    //                     world->ConvertIndexToCoord(desiredPath[i], x, y);
    //                     world->SwapElement(this->x, this->y, x, y);
    //                 }
    //             }
    //             else {
    //                 int x = 0;
    //                 int y = 0;
    //                 world->ConvertIndexToCoord(desiredPath[i], x, y);
    //
    //                 if (!world->IsInsideBounds(x, y) || world->GetElement(x, y) != nullptr) {
    //
    //                     world->SwapElement(this->x, this->y, x, y);
    //                 }
    //             }
    //
    //
    //             //std::cout << "c" + std::to_string(desiredPath[i])  << "x" + std::to_string(x) << "y" + std::to_string(y) << std::endl;
    //
    //         }
    //     } else {
    //         vY = 0;
    //         vX = 0;
    //     }
    }

    // if (world->GetElement(x, y + 1) == nullptr) {
    //     vY += world->gravity * GetFrameTime();
    //
    //     int pixelsToMove = std::ceil(vY);
    //     for (int i = 0; i < pixelsToMove; i++) {
    //         if (!world->IsInsideBounds(x, y + 1)) break;
    //
    //         if (world->GetElement(x, y + 1) == nullptr) {
    //             world->SwapElement(x, y, x, y + 1);
    //         };
    //     }
    // }
    // else {
    //     int direction = 1;
    //     direction = random_val_int(0, 1) ? direction : -direction;
    //     if (!goDiagonal(direction)) {
    //         goDiagonal(-direction);
    //     }
    // }

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