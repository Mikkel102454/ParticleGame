//
// Created by mikkel on 1/27/2026.
//

#include "game/world/element.h"
#include "game/world/world.h"

void Element::Draw(int prevX, int prevY) const {
    ImageDrawPixel(&world->img, prevX, prevY, WHITE);
    ImageDrawPixel(&world->img, x, y, GetColor());
}