#include "game/world/elements/solid/movable/sand.h"

void Sand::Step() {
    if (y >= GetScreenHeight()) {
        active = false;
        return;
    }

    int prevX, prevY;
    prevX = x;
    prevY = y;

    bool moved = false;

    if (world->map[x * world->height + y + 1] == nullptr) {
        world->map[x * world->height + y + 1] = this;
        world->map[x * world->height + y] = nullptr;

        y += 1;
        moved = true;
    }
    else if (world->directionPrefer == 1) {
        if (!goDiagonal(1)) {
            if (goDiagonal(-1)) moved = true;
        } else moved = true;
    } else {
        if (!goDiagonal(-1)) {
            if (goDiagonal(1)) moved = true;
        } else moved = true;
    }

    if (!moved) {
        active = false;
        return;
    }

    Draw(prevX, prevY);
    Update_Nearby();
}

bool Sand::goDiagonal(int direction) {
    if (x > 0 && x < world->width - 1 && world->map[(x + direction) * world->height + y + 1] == nullptr) {
        world->map[(x + direction) * world->height + y + 1] = this;
        world->map[x * world->height + y] = nullptr;

        x += direction;
        y += 1;
        return true;
    }
    return false;
}