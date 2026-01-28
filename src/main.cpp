#include <algorithm>
#include <iostream>
#include <random>

#include <raylib.h>

#include "../include/game/world/world.h"
#include "game/devtools.h"
#include "game/world/element.h"
#include "game/utils/numbers.h"
#include "game/world/elements/liquid/water.h"
#include "game/world/elements/solid/immovable/wood.h"
#include "game/world/elements/solid/movable/sand.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main()
{
    enum Types {
        SAND,
        WATER,
        WOOD
    };
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1080;
    const int screenHeight = 720;

    const int targetFps = 120;

    InitWindow(screenWidth, screenHeight, "Uno");

    SetTargetFPS(targetFps);
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

    int lastY = world->height - 1;
    Types spawnType = SAND;
    // Main game loop
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_C)) spawnType = SAND;
        else if (IsKeyPressed(KEY_V)) spawnType = WATER;
        else if (IsKeyPressed(KEY_B)) spawnType = WOOD;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            int mx = GetMouseX();
            int my = GetMouseY();

            for (int dx = -5; dx <= 5; dx++) {
                for (int dy = -5; dy <= 5; dy++) {
                    switch (spawnType) {
                        case SAND:
                            world->SpawnElement(mx + dx, my + dy, new Sand());
                            break;
                        case WATER:
                            world->SpawnElement(mx + dx, my + dy, new Water());
                            break;
                        case WOOD:
                            world->SpawnElement(mx + dx, my + dy, new Wood());
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
                    world->DeleteElement(x, y);
                }
            }
        }

        if (IsKeyPressed(KEY_F2)) {
            if (Is_Devtool_Active()) Deactivate_Devtool();
            else Activate_Devtool(world);
        }
        //Reset Updates
        // Update
        for (size_t i = world->width * world->height; i-- > 0; ) {
            if (world->map[i] == nullptr) continue;
            world->map[i]->hasSteppedThisFrame = false;
        }

        // Update
        static bool flip = false;
        flip = !flip;


        // if (IsKeyPressed(KEY_F)) {
        //     if (!flip) {
        //         for (int x = 0; x < world->width; ++x) {
        //             size_t i = lastY * world->width + x;
        //             if (world->map[i] == nullptr || world->map[i]->hasSteppedThisFrame) continue;
        //             world->map[i]->hasSteppedThisFrame = true;
        //             world->map[i]->Step();
        //         }
        //     } else {
        //         for (int x = world->width - 1; x >= 0; --x) {
        //             size_t i = lastY * world->width + x;
        //             if (world->map[i] == nullptr || world->map[i]->hasSteppedThisFrame) continue;
        //             world->map[i]->hasSteppedThisFrame = true;
        //             world->map[i]->Step();
        //         }
        //     }
        //     lastY--;
        //     if (lastY < 0) lastY = world->height - 1;
        // }
        for (int y = world->height - 1; y >= 0; --y) {

            if (!flip) {
                for (int x = 0; x < world->width; ++x) {
                    size_t i = y * world->width + x;
                    if (world->map[i] == nullptr || world->map[i]->hasSteppedThisFrame) continue;
                    world->map[i]->hasSteppedThisFrame = true;
                    world->map[i]->Step();
                }
            } else {
                for (int x = world->width - 1; x >= 0; --x) {
                    size_t i = y * world->width + x;
                    if (world->map[i] == nullptr || world->map[i]->hasSteppedThisFrame) continue;
                    world->map[i]->hasSteppedThisFrame = true;
                    world->map[i]->Step();
                }
            }
        }

        if (Is_Devtool_Active()) {
            Devtool_Tick();
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

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadTexture(world->texture);

    CloseWindow();        // Close window and OpenGL context

    return 0;
}