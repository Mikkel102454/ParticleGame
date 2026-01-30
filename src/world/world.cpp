//
// Created blocation->y mikkel on 1/26/2026.
//

#include "game/world/world.h"

#include <cmath>

#include "game/world/element.h"
#include "game/world/elements/solid/movable/sand.h"


void World::SpawnElement(int x, int y, Element* element) {
    if (!IsInsideBounds(x, y)) return;
    if (GetElement(x, y) != nullptr) return;

    element->x = x;
    element->y = y;
    element->world = this;
    element->isActive = true;

    element->Draw(x, y);
    map[y * width + x] = element;

}

Element* World::GetElement(int x, int y) const {
    return map[y * width + x];
}
Element* World::GetElement(int i) const {
    return map[i];
}

void World::SetElement(int x, int y, Element* element) const {
    map[y * width + x] = element;
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

std::vector<int> World::ComputeTraverse(int x, int y, float vX, float vY) const
{
    std::vector<int> arr;

    // Convert float movement to grid delta
    int dx = std::ceil(vX);
    int dy = std::ceil(vY);

    if (dx == 0 && dy == 0)
        return arr;

    int stepX = dx < 0 ? -1 : 1;
    int stepY = dy < 0 ? -1 : 1;

    dx = std::abs(dx);
    dy = std::abs(dy);

    int index = 0;

    //Left and right only
    if (dy == 0) {
        arr.resize(dx);
        for (int i = 0; i < dx; i++) {
            int _x = x + (i + 1) * stepX;
            int _y = y;
            arr[index++] = _y * width + _x;
        }
        return arr;
    }

    //Up and down only
    if (dx == 0) {
        arr.resize(dy);
        for (int i = 0; i < dy; i++) {
            int _x = x;
            int _y = y + (i + 1) * stepY;
            arr[index++] = _y * width + _x;
        }
        return arr;
    }

    if (dx >= dy) {
        float slope = (float)dy / (float)dx;
        float yAcc = slope;

        arr.resize(dx);
        for (int i = 1; i <= dx; i++) {
            int _x = x + i * stepX;
            int _y = y + (int)(yAcc + 0.5f) * stepY;
            arr[index++] = _y * width + _x;
            yAcc += slope;
        }
    } else {
        float slope = (float)dx / (float)dy;
        float xAcc = slope;

        arr.resize(dy);
        for (int i = 1; i <= dy; i++) {
            int _x = x + (int)(xAcc + 0.5f) * stepX;
            int _y = y + i * stepY;
            arr[index++] = _y * width + _x;
            xAcc += slope;
        }
    }

    return arr;
}

void World::ConvertIndexToCoord(int i, int& x, int& y) const {
    y = std::floor( i / width);
    x = i % width;
}

void World::ActivateArea(int x, int y) const {
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0 || !IsInsideBounds(x + dx, y + dy)) continue;
            Element* element = GetElement(x + dx, y + dy);
            if (element == nullptr) continue;
            element->isActive = true;
        }
    }
}
