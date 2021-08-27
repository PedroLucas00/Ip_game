#include "raylib.h"

// Define functions
void menu(int width, int height);
void gameplay(int width, int height);

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

void gameplay(int width, int height){

    int windowDimensions[2];
    windowDimensions[0] = width; // x
    windowDimensions[1] = height; // y


    // acceleration due to gravity (pixels/s)/s
    float gravity = 0;
    float acceleration = 1.5;
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
        if(IsKeyDown(KEY_SPACE) && isOnGround(scarfyData, windowDimensions[1])){
            gravity -= 30;
            scarfyData.pos.y -= 1;

        }else if (IsKeyDown(KEY_SPACE) && !isOnGround(scarfyData, windowDimensions[1]) && gravity >= 1)
        {
            acceleration = 0.18;
        }else{
            if(!isOnGround(scarfyData, windowDimensions[1]))
            acceleration = 1.5;
        }
        if(isOnGround(scarfyData, windowDimensions[1])){
            scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
            gravity = 1;   
        } 
        gravity += acceleration;

        // Tiro do player
        

        // stop drawing
        EndDrawing();
    }
}

void menu(int width, int height){
    
    // Menu Variables
    int selected_menu_option = 1;
    int text_menu_size = 45;
    // Define Menu Background Image
    Texture2D menu_background = LoadTexture("images/menu_background.png");
    // Loop while waiting for a ENTER press
    while(!IsKeyDown(KEY_ENTER)){
        // Menu Work Flow
        if(selected_menu_option==3) selected_menu_option = 1;
        if(selected_menu_option==0) selected_menu_option = 2;
        if(IsKeyReleased(KEY_UP)) selected_menu_option--;
        if(IsKeyReleased(KEY_DOWN)) selected_menu_option++;
        // Menu Drawing
        BeginDrawing();
        DrawTexture(menu_background, 0, 0, WHITE);
        if(selected_menu_option==1){
            DrawText("PLAY", 286, 372, text_menu_size, RED);
            DrawText("QUIT", 284, 581, text_menu_size, WHITE);
        }
        else if(selected_menu_option==2){
            DrawText("PLAY", 286, 372, text_menu_size, WHITE);
            DrawText("QUIT", 284, 581, text_menu_size, RED);
        }
        EndDrawing();
    }
    // After press ENTER key
    if(selected_menu_option==1) gameplay(width, height);
    if(selected_menu_option==2) CloseWindow();
}

int main(void){
    // array with window dimensions
    int windowDimensions[2];
    windowDimensions[0] = 1280; // x
    windowDimensions[1] = 720; // y

    InitWindow(windowDimensions[0], windowDimensions[1], "A code adventure");

    
    // Game FPS
    SetTargetFPS(60);
    
    // Menu
    menu(windowDimensions[0], windowDimensions[1]);
    
    // THE END
    CloseWindow();
}