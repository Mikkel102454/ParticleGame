#include <algorithm>
#include <iostream>
#include <random>

#include <raylib.h>

#include "../include/game/world/world.h"
#include "game/world/element.h"
#include "game/utils/numbers.h"
#include "game/world/elements/liquid/water.h"
#include "game/world/elements/solid/movable/sand.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main()
{
    enum Types {
        SAND,
        WATER
    };
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1080;
    const int screenHeight = 720;

    const int targetFps = 120;

    InitWindow(screenWidth, screenHeight, "Uno");

    SetTargetFPS(targetFps);               // Set our game to run at 120 frames-per-second
    SetExitKey(KEY_NULL);

    World* world = new World();
    world->id = 0;
    world->width = screenWidth;
    world->height = screenHeight;
    world->img = GenImageColor(screenWidth, screenHeight, WHITE);
    world->texture = LoadTextureFromImage(world->img);
    world->map = new Element *[world->width * world->height]();

    //--------------------------------------------------------------------------------------

    int startX = 0;
    int startY = 0;

    Types spawnType = SAND;
    // Main game loop
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_C)) spawnType = SAND;
        else if (IsKeyPressed(KEY_V)) spawnType = WATER;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            int mx = GetMouseX();
            int my = GetMouseY();

            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    switch (spawnType) {
                        case SAND:
                            world->Spawn_Element(mx + dx, my + dy, new Sand());
                            break;
                        case WATER:
                            world->Spawn_Element(mx + dx, my + dy, new Water());
                            break;
                    }
                }
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            startX = GetMouseX();
            startY = GetMouseY();
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
            int endX = GetMouseX();
            int endY = GetMouseY();

            int minX = std::min(startX, endX);
            int maxX = std::max(startX, endX);
            int minY = std::min(startY, endY);
            int maxY = std::max(startY, endY);

            for (int x = minX; x <= maxX; x++) {
                for (int y = minY; y <= maxY; y++) {
                    world->Delete_Element(x, y);
                }
            }
        }

        world->directionPrefer = randomChance(0.5f) ? 1 : 0;

        std::sort(world->activeBlocks.begin(), world->activeBlocks.end(),
            [](Element* a, Element* b) {
                return a->y > b->y;
            }
        );

        // Update
        for (size_t i = 0; i < world->activeBlocks.size(); ) {
            Element* element = world->activeBlocks[i];
            if (element == nullptr || !element->active) {
                world->activeBlocks[i] = world->activeBlocks.back();
                world->activeBlocks.pop_back();
                continue;
            }

            element->Step();

            if (!element->active) {
                world->activeBlocks[i] = world->activeBlocks.back();
                world->activeBlocks.pop_back();
            } else {
                i++;
            }
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        UpdateTexture(world->texture, world->img.data);
        DrawTexture(world->texture, 0, 0, WHITE);

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            DrawRectangleLines(GetMouseX(), GetMouseY(), startX - GetMouseX(), startY - GetMouseY(), RED);
        }

        DrawText(TextFormat("CURRENT FPS: %i", (int)(1/GetFrameTime())), GetScreenWidth() - 220, 40, 20, GREEN);
        DrawText(TextFormat("ACTIVE PIXELS: %i", world->activeBlocks.size()), GetScreenWidth() - 220, 90, 20, GREEN);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadTexture(world->texture);

    CloseWindow();        // Close window and OpenGL context

    return 0;
}