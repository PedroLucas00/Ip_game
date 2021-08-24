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
    int width = 800;
    int height = 450;
    InitWindow(width, height, "Titulo desse ngc");

    

    // Gravidade 
    const int gravity = 500;

    
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE); 
        
        if(){
            DrawText("Game over!", 400, 200, 20, RED); 
        }else{
            // Logica start

        }

        // Logica end
        EndDrawing();
    }
    CloseWindow();
    return 0;
}