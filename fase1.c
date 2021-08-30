#include "raylib.h"

void fase1(int width, int height){

    while(!WindowShouldClose()){

        ClearBackground(WHITE);

        BeginDrawing();
        //Base
        DrawRectangle(0, 620, 200, 100, BLACK);
        DrawRectangle(300, 620, 400, 100, BLACK);
        
        //Stairs blocks
        DrawRectangle(750, 520, 70, 20, BLACK);
        DrawRectangle(850, 420, 70, 20, BLACK);
        DrawRectangle(650, 320, 70, 20, BLACK);

        //Top blocks
        DrawRectangle(200, 300, 350, 20, BLACK);
        DrawRectangle(75, 175, 70, 20, BLACK);
        DrawRectangle(250, 150, 1030, 20, BLACK);

        EndDrawing();
    }
}