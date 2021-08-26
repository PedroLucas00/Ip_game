#include "raylib.h"

typedef struct 
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
}AnimData;

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}


int main()
{
    // array with window dimensions
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;

    // initialize the window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");

    // acceleration due to gravity (pixels/s)/s
    const int gravity = 1000;

    


    // scarfy variables
    AnimData scarfyData;
    scarfyData.rec.width = 50;
    scarfyData.rec.height = 50;
    scarfyData.rec.x = 50;
    scarfyData.rec.y = 50;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangle(scarfyData.pos.x, scarfyData.pos.y, scarfyData.rec.width, scarfyData.rec.height, RED);

        // controles basicos 
        if (IsKeyDown(KEY_D))
        {
            scarfyData.pos.x += 10;
        }
        if (IsKeyDown(KEY_A))
        {
            scarfyData.pos.x -= 10;
        }if (IsKeyDown(KEY_W))
        {
            scarfyData.pos.y -= 10;
        }if (IsKeyDown(KEY_S))
        {
            scarfyData.pos.y += 10;
        }

        // stop drawing
        EndDrawing();
    }
     
    CloseWindow();
}