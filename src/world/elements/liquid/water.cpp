#include "game/world/elements/liquid/water.h"

#include "game/utils/random.h"

void Water::Step() {
    int prevX = x;
    int prevY = y;

    // Down
    if (world->IsInsideBounds(x, y + 1) && world->GetElement(x, y + 1) == nullptr) {

        world->SetElement(x, y + 1, this);
        world->SetElement(x, y, nullptr);
        y += 1;
    }
    // Down-left
    else if (world->IsInsideBounds(x - 1, y + 1) && world->GetElement(x - 1, y + 1) == nullptr) {

        world->SetElement(x - 1, y + 1, this);
        world->SetElement(x, y, nullptr);
        x -= 1;
        y += 1;
    }
    // Down-right
    else if (world->IsInsideBounds(x + 1, y + 1) && world->GetElement(x + 1, y + 1) == nullptr) {

        world->SetElement(x + 1, y + 1, this);
        world->SetElement(x, y, nullptr);
        x += 1;
        y += 1;
    }
    // Left
    else if (world->IsInsideBounds(x - 1, y) && world->GetElement(x - 1, y) == nullptr) {

        world->SetElement(x - 1, y, this);
        world->SetElement(x, y, nullptr);
        x -= 1;
    }
    // Right
    else if (world->IsInsideBounds(x + 1, y) && world->GetElement(x + 1, y) == nullptr) {

        world->SetElement(x + 1, y, this);
        world->SetElement(x, y, nullptr);
        x += 1;
    }
    else {
        int direction = 1;
        direction = random_val_int(0, 1) ? direction : -direction;
        if (world->IsInsideBounds(x + direction, y) && world->GetElement(x + direction, y) == nullptr) {

            world->SetElement(x + direction, y, this);
            world->SetElement(x, y, nullptr);
            x += direction;
        } else if (world->IsInsideBounds(x + -direction, y) && world->GetElement(x + -direction, y) == nullptr) {

            world->SetElement(x + -direction, y, this);
            world->SetElement(x, y, nullptr);
            x += -direction;
        }
    }

    Draw(prevX, prevY);
}
