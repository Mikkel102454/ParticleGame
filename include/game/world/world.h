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

    Element** map;

    std::list<Element*> blocks;
    std::vector<Element*> activeBlocks;

    Image img;
    Texture texture;

    int directionPrefer;

    void Spawn_Element(int x, int y, Element* element);
    void Delete_Element(int x, int y);
} World;


#endif //UNA_WORLD_H