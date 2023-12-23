#include <iostream>
#include "raylib.h"
#include "Game.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
//--------Globals--------
double lastUpdatedTime = 0.0;
double MOVEMENT_RATE = 0.2;
//-----------------------

bool triggerEvent(double interval) {
    auto currentTime = GetTime();

    if (currentTime - lastUpdatedTime >= interval) {
        lastUpdatedTime = currentTime;
        return true;
    }

    return false;
}
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 500;
    const int screenHeight = 620;
    Game game;


    InitWindow(screenWidth, screenHeight, "raylib tetris game");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        game.handleInput();
        UpdateMusicStream(game.music);
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        if (triggerEvent(MOVEMENT_RATE)) {
            game.moveBlockDown();
        }

        ClearBackground({ 37,37,37 });



        DrawText("Score", 365, 13, 38, RED);
        DrawText("Next", 370, 175, 38, RED);
        if (game.gameOver) {
            DrawText("GAME OVER", 320, 450, 29, RED);
        }
        DrawRectangleRounded({ 320, 55, 170, 60 }, 0.3, 6, { 30,30,30, 255});

        char score[10];
        sprintf_s(score, "%d", game.score);
        auto textSize = MeasureTextEx(Font(), score, 38, 2);

        DrawTextEx(Font(), score, {320 + (150 - textSize.x) / 2, 65}, 38, 2, RED);

        DrawRectangleRounded({ 320, 215, 170, 180 }, 0.3, 6, { 30,30,30,255 });
        game.draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

