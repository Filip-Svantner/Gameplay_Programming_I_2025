#include "raylib.h"
#include "stdio.h"

#include "../include/game.h"

// Specific include for build_web
#if defined(WEB_BUILD)
#include <emscripten/emscripten.h>
#endif

const int screenWidth = 800;
const int screenHeight = 600;

void GameLoop(void);

int main(void)
{

    InitWindow(screenWidth, screenHeight, "Raylib StarterKit GPPI");

    // Initialise Game
    InitGame();

    // For web builds, do not use WindowShouldClose
    // see https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)#41-avoid-raylib-whilewindowshouldclose-loop

#if defined(WEB_BUILD)
    emscripten_set_main_loop(GameLoop, 0, 1);
#else
    SetTargetFPS(60);
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Call GameLoop
        GameLoop();
    }
#endif

    // Free resources
    CloseGame();

    CloseWindow();

    return 0;
}

void GameLoop(void)
{
    BeginDrawing();

    // Update Game Data
    // Should be outside BeginDrawing(); and EndDrawing();
    UpdateGame();

    ClearBackground(RAYWHITE);
    
    DrawCircle(200,200,50,RED);
    DrawRectangle(700, 200, 80, 40, BLUE);
    DrawLine(10, 10, 300, 100, GREEN);
    DrawTriangle((Vector2){0, 500}, (Vector2){300, 500}, (Vector2){300, 400}, PURPLE);
    

    // Draw the Game Objects
    DrawGame();


    EndDrawing();
}
