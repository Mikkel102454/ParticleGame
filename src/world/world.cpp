//
// Created blocation->y mikkel on 1/26/2026.
//

#include "game/world/world.h"
#include "game/world/element.h"
#include "game/world/elements/solid/movable/sand.h"


void World::SpawnElement(int x, int y, Element* element) {
    if (!IsInsideBounds(x, y)) return;
    if (GetElement(x, y) != nullptr) return;

    element->x = x;
    element->y = y;
    element->world = this;

    element->Draw(x, y);
    map[x * height + y] = element;
}

Element* World::GetElement(int x, int y) const {
    return map[x * height + y];
}
void World::SetElement(int x, int y, Element* element) const {
    map[x * height + y] = element;
}

void World::ConvertFromIndexToCoord(int index, int& x, int& y) const {
    if (index < 0 || index >= height * width) return;
}

void World::SwapElement(int x1, int y1, int x2, int y2) const {
    Element* element1 = GetElement(x1, y1);
    Element* element2 = GetElement(x2, y2);

    SetElement(x1, y1, element2);
    SetElement(x2, y2, element1);

    if (element1 != nullptr) {
        element1->x = x2;
        element1->y = y2;
        if (element2 == nullptr) element1->Draw(x1, y1);
        element1->Draw(x2, y2);
    }
    if (element2 != nullptr) {
        element2->x = x1;
        element2->y = y1;

        if (element1 == nullptr) element2->Draw(x2, y2);
        element2->Draw(x1, y1);
    }
}


bool World::IsInsideBounds(int x, int y) const {
    if (y >= height || y < 0) return false;
    if (x >= width || x < 0) return false;
    return true;
}

void World::DeleteElement(int x, int y) {
    if (!IsInsideBounds(x, y)) return;
    if (GetElement(x, y) == nullptr) return;

    ImageDrawPixel(&img, x, y, WHITE);

    SetElement(x, y, nullptr);
}

void World::ComputeTraverse(int x, int y, float vX, float vY, int& arr) const {
    if (vY == 0) {
        int amount = vX < 0 ? -1 : 1;
        vX = vX < 0 ? -vX : vX;

        for (int i = 0; i < vY; i++) {
            int _x = x;
            int _y = y;
            arr[i] = _x * height + _y;;
        }
        return;
    }
    if (vX == 0) {
        int amount = vX < 0 ? -1 : 1;
        vX = vX < 0 ? -vX : vX;

        for (int i = 0; i < vX; i++) {
            arr[i] = x - amount * (i + 1);
        }
        return;
    }

    float slope = (y + vY - y / (x + vX - x));

    arr = new int[vX];
    vX = vX < 0 ? -vX : vX;

    for (int i = 0; i < vX; i++) {
        int _x = x + i;
        int _y = y + slope * i + 1;
        arr[i] = _x * height + _y;
    }
}
