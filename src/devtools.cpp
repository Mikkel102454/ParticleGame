//
// Created by mikkel on 1/28/2026.
//

#include "game/devtools.h"

#include "game/world/element.h"

bool isActive;
World* world;

void Activate_Devtool(World* w) {
    if (isActive) return;
    isActive = true;
    world = w;
}

void Deactivate_Devtool() {
    if (!isActive) return;
    isActive = false;

    for (int x = 0; x < world->width; x++) {
        for (int y = 0; y < world->height; y++) {
            if (world->GetElement(x, y) == nullptr) {
                ImageDrawPixel(&world->img, x, y, WHITE);
            }
            else {
                world->GetElement(x, y)->Draw(x, y);
            }
        }
    }
}

bool Is_Devtool_Active() {
    return isActive;
}

void Devtool_Tick() {
    for (int x = 0; x < world->width; x++) {
        for (int y = 0; y < world->height; y++) {
            if (world->GetElement(x, y) == nullptr) {
                ImageDrawPixel(&world->img, x, y, BLACK);
            }
            else {
                ImageDrawPixel(&world->img, x, y, WHITE);
            }
        }
    }
}