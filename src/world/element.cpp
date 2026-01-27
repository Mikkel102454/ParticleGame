//
// Created by mikkel on 1/27/2026.
//

#include "game/world/element.h"
#include "game/world/world.h"

void Element::Draw(int prevX, int prevY) const {
    ImageDrawPixel(&world->img, prevX, prevY, WHITE);
    ImageDrawPixel(&world->img, x, y, GetColor());
}

void Element::Update_Nearby() const {
    for (int dx = -2; dx <= 2; dx++) {
        for (int dy = -2; dy <= 2; dy++) {
            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;

            if (nx < 0 || ny < 0 ||
                nx >= GetScreenWidth() || ny >= GetScreenHeight())
                continue;

            Element* m = world->map[nx * world->height + ny];
            if (m != nullptr && !m->active) {
                m->active = true;
                world->activeBlocks.push_back(m);
            }
        }
    }
}