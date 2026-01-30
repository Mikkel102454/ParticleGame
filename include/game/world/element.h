#ifndef UNA_ELEMENT_H
#define UNA_ELEMENT_H
#include "raylib.h"
#include "world.h"

typedef struct Element {
    virtual void Step() = 0;
    virtual Color GetColor() const = 0;
    virtual float GetMass() const = 0;
    virtual void ReceiveHeat() = 0;

    void Draw(int prevX, int prevY) const;

    World* world;

    int x;
    int y;

    float vX;
    float vY;

    bool hasSteppedThisFrame;
    bool isActive;

} Element;

#endif //UNA_ELEMENT_H