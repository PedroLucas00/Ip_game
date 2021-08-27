/* #include "raylib.h"

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
    SetTargetFPS(60);

    // array with window dimensions
    int windowDimensions[2];
    windowDimensions[0] = 1280; // x
    windowDimensions[1] = 720; // y

    // initialize the window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");

    // acceleration due to gravity (pixels/s)/s
    int gravity = 0;
    int acceleration = 1.5;
    int temp;
    


    // player variables
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

    
    while (!WindowShouldClose())
    {
        gravity += acceleration;
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangle(scarfyData.pos.x, scarfyData.pos.y, scarfyData.rec.width, scarfyData.rec.height, RED);
        // gravidade
        
        if(!isOnGround(scarfyData, windowDimensions[1])){
            scarfyData.pos.y += gravity;
        };

        // controles basicos 
        if (IsKeyDown(KEY_D))
        {
            scarfyData.pos.x += 10;
        }
        if (IsKeyDown(KEY_A))
        {
            scarfyData.pos.x -= 10;
        }
        if(IsKeyPressed(KEY_SPACE) && isOnGround(scarfyData, windowDimensions[1])){
            gravity -= 30;
            scarfyData.pos.y -= 1;

        }else if (IsKeyDown(KEY_SPACE) && !isOnGround(scarfyData, windowDimensions[1]) && gravity >= 0)
        {
            acceleration = 0.25;
        }else{
            if(!isOnGround(scarfyData, windowDimensions[1]))
            acceleration = 1.5;
        }
        if(isOnGround(scarfyData, windowDimensions[1])){
            scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
            gravity = 1;
        } 
        // stop drawing
        EndDrawing();
    }
     
    CloseWindow();
} */