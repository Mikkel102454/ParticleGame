#ifndef UNA_ELEMENT_H
#define UNA_ELEMENT_H
#include "raylib.h"
#include "world.h"

typedef struct Element {
    virtual void Step() = 0;
    virtual Color GetColor() const = 0;
    virtual void ReceiveHeat() = 0;

    void Draw(int prevX, int prevY) const;
    void Update_Nearby() const;

    World* world;

    int x;
    int y;

    bool active;

} Element;

#endif //UNA_ELEMENT_H