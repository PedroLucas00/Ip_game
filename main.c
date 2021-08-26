#include "raylib.h"

int main(void){
    // Janela
    int width = 1280;
    int height = 720;
    InitWindow(width, height, "A Code Adventure");

    // Circulo
    int circle_x = width/3;
    int circle_y = height/3;
    int circle_radius = 25;

    // Cantos do circulo
    int l_circle_x = circle_x - circle_radius;
    int r_circle_x = circle_x + circle_radius;
    int u_circle_y = circle_y - circle_radius;
    int b_circle_y = circle_y + circle_radius;

    // Axe coordinates
    int axe_x = 300;
    int axe_y = 0;
    int axe_length = 50;

    int direction = 10;

    // Axe cantos
    int l_axe_x = axe_x;
    int r_axe_x = axe_x + axe_length;
    int u_axe_y = axe_y;
    int b_axe_y = axe_y + axe_length;

    bool collision_with_axe =
        (b_axe_y >= u_circle_y) &&
        (u_axe_y <= b_circle_y) &&
        (l_axe_x <= r_circle_x) &&
        (r_axe_x >= l_circle_x);

    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        if(collision_with_axe){
            int GAMEOVER_fontsize = 60;
            DrawText("GAME OVER", width/16, height-(height/4), GAMEOVER_fontsize, RED);

            if(IsKeyDown(KEY_SPACE))
            {
                circle_x = width/3;
                circle_y = height/3;

                axe_x = 300;
                axe_y = 0;

                collision_with_axe = 0;
            }
        }else{

            // update cantos
            l_circle_x = circle_x - circle_radius;
            r_circle_x = circle_x + circle_radius;
            u_circle_y = circle_y - circle_radius;
            b_circle_y = circle_y + circle_radius;

            l_axe_x = axe_x;
            r_axe_x = axe_x + axe_length;
            u_axe_y = axe_y;
            b_axe_y = axe_y + axe_length;

            // Update collision
            collision_with_axe =
                (b_axe_y >= u_circle_y) &&
                (u_axe_y <= b_circle_y) &&
                (l_axe_x <= r_circle_x) &&
                (r_axe_x >= l_circle_x);

            // Logica start

            DrawCircle(circle_x, circle_y, circle_radius, BLUE);
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

            axe_y += direction;
            if( axe_y > height || axe_y < 0){
                direction = -direction;
            }

            if(IsKeyDown(KEY_D) && circle_x < width){
                circle_x += 10;
            }
            if(IsKeyDown(KEY_A) && circle_x > 0){
                circle_x -= 10;
            }
            if(IsKeyDown(KEY_W)){
                circle_y -= 10;
            }
            if(IsKeyDown(KEY_S)){
                circle_y += 10;
            }

        }

        // Logica end
        EndDrawing();
    }
    CloseWindow();
    return 0;
}