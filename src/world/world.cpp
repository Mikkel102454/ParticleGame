//
// Created by mikkel on 1/26/2026.
//

#include "game/world/world.h"
#include "game/world/element.h"
#include "game/world/elements/solid/movable/sand.h"


void World::Spawn_Element(int x, int y, Element* element) {
    if (y >= height || y < 0) return;
    if (x >= width || x < 0) return;
    if (map[x * height + y] != nullptr) return;

    element->x = x;
    element->y = y;
    element->world = this;
    element->active = true;

    element->Draw(x, y);
    map[x * height + y] = element;
    blocks.push_back(element);
    activeBlocks.push_back(element);

}

void World::Delete_Element(int x, int y) {
    if (y >= height || y < 0) return;
    if (x >= width || x < 0) return;
    if (map[x * height + y] == nullptr) return;

    ImageDrawPixel(&img, x, y, WHITE);

    map[x * height + y]->active = false;
    map[x * height + y] = nullptr;
}
