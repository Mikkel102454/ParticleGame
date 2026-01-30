//
// Created by mikkel on 1/26/2026.
//

#ifndef UNA_WORLD_H
#define UNA_WORLD_H
#include <list>
#include <vector>

#include "raylib.h"

struct Element;

typedef struct World {
    int id;

    int width;
    int height;
    float gravity = 10;

    Element** map;

    Image img;
    Texture texture;

    void SpawnElement(int x, int y, Element* element);

    void DeleteElement(int x, int y);

    Element* GetElement(int x, int y) const;
    Element* GetElement(int i) const;

    void SwapElement(int x1, int y1, int x2, int y2) const;

    bool IsInsideBounds(int x, int y) const;
    void SetElement(int x, int y, Element* element) const;

    std::vector<int> ComputeTraverse(int x, int y, float vX, float vY) const;

    void ConvertIndexToCoord(int i, int& x, int& y) const;

    void ActivateArea(int x, int y) const;
} World;


#endif //UNA_WORLD_H