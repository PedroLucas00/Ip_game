#include "raylib.h"


typedef struct 
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
}AnimData; // Toda coisa animada deve ter um desses pra simplificar o cabeçalho

bool isOnGround(AnimData data, int windowHeight) // check se tá no chão
{
    return data.pos.y >= windowHeight - data.rec.height;
}

int main(void){
    // Janela
    int window_width = 800;
    int window_height = 450;
    InitWindow(window_width, window_height, "Joguinho IP");
    SetTargetFPS(60);

    // Gravidade 
    const int gravity = 500;
    Texture2D player = LoadTexture("textures/scarfy.png");
    AnimData player_data;
    player_data.rec.width = player.width/6;
    player_data.rec.height = player.height;
    player_data.rec.x = 0;
    player_data.rec.y = 0;
    player_data.pos.x = window_width/2 - player_data.rec.width/2;
    player_data.pos.y = window_height - player_data.rec.height;
     

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        
        if(0){ //if deve ser game over
            DrawText("Game over!", 400, 200, 20, RED); 
        }else{
            // Logica start
            DrawRectangle(0, 0, 50, 50, RED);
            if 
            




        }

        // Logica end
        EndDrawing();
    }
    CloseWindow();
    return 0;
}