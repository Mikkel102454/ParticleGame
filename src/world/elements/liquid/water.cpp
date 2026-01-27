#include "game/world/elements/liquid/water.h"

void Water::Step() {
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
    else if (world->map[x - 1 * world->height + y] == nullptr) {
        world->map[x - 1 * world->height + y] = this;
        world->map[x * world->height + y] = nullptr;

        x -=1 ;
        moved = true;
    }
    else if (world->map[x + 1 * world->height + y] == nullptr) {
        world->map[x + 1 * world->height + y] = this;
        world->map[x * world->height + y] = nullptr;

        x +=1 ;
        moved = true;
    }

    if (!moved) {
        //active = false;
        //return;
    }

    Draw(prevX, prevY);
    Update_Nearby();
}
