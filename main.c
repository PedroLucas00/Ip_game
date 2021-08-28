#include "raylib.h"

// Game screens
typedef enum{
    MENU,
    GAMEPLAY,
    RESUME,
    DEATH,
    QUIT,
}screen;

// Define functions
int menu(int width, int height);
int gameplay(int width, int height);
int pause(int width, int height);
int death(int width, int height);

// Pause menu
int pause(int width, int height){
    // Pause Menu Variables
    int selected_pausemenu_option = 1;
    // Define PAUSE font size
    int PAUSE_fontsize = 60;
    // Define text font size
    int TEXT_fontsize = 46;
    // Define Pause Background Image
    Texture2D pause_background = LoadTexture("images/pause_menu_background.png");
    // Loop while waiting for a ENTER press
    while(!IsKeyReleased(KEY_ENTER)){
        // Menu Work Flow
        if(selected_pausemenu_option==4) selected_pausemenu_option = 1;
        if(selected_pausemenu_option==0) selected_pausemenu_option = 3;
        if(IsKeyReleased(KEY_UP)) selected_pausemenu_option--;
        if(IsKeyReleased(KEY_DOWN)) selected_pausemenu_option++;
        // Menu Drawing
        BeginDrawing();
        DrawTexture(pause_background, 416, 218, WHITE);
        DrawText("PAUSE", (width-width/2)-PAUSE_fontsize, height-(height/4), PAUSE_fontsize, WHITE);
        if(selected_pausemenu_option==1){
            DrawText("RESUME", 545, 268, TEXT_fontsize, RED);
            DrawText("GO TO MENU", 499, 339, TEXT_fontsize, WHITE);
            DrawText("QUIT", 586, 411, TEXT_fontsize, WHITE);
        }
        else if(selected_pausemenu_option==2){
            DrawText("RESUME", 545, 268, TEXT_fontsize, WHITE);
            DrawText("GO TO MENU", 499, 339, TEXT_fontsize, RED);
            DrawText("QUIT", 586, 411, TEXT_fontsize, WHITE);
        }
        else if(selected_pausemenu_option==3){
            DrawText("RESUME", 545, 268, TEXT_fontsize, WHITE);
            DrawText("GO TO MENU", 499, 339, TEXT_fontsize, WHITE);
            DrawText("QUIT", 586, 411, TEXT_fontsize, RED);
        }
        EndDrawing();
    }
    // After press ENTER key
    if(selected_pausemenu_option==1) return RESUME;
    if(selected_pausemenu_option==2) return MENU;
    if(selected_pausemenu_option==3) return QUIT;
}

// Death menu
int death(int width, int height){
    // Death Menu Variables
    int selected_deathmenu_option = 1;
    // Define GAMEOVER font size
    int GAMEOVER_fontsize = 60;
    // Define text font size
    int TEXT_fontsize = 45;
    // Define Death Background Image
    Texture2D death_background = LoadTexture("images/death_background.png");
    // Loop while waiting for a ENTER press
    while(!IsKeyReleased(KEY_ENTER)){
        // Menu Work Flow
        if(selected_deathmenu_option==4) selected_deathmenu_option = 1;
        if(selected_deathmenu_option==0) selected_deathmenu_option = 3;
        if(IsKeyReleased(KEY_UP)) selected_deathmenu_option--;
        if(IsKeyReleased(KEY_DOWN)) selected_deathmenu_option++;
        // Menu Drawing
        BeginDrawing();
        DrawTexture(death_background, 0, 0, WHITE);
        DrawText("GAME OVER", width-width/3, height-(height/6), GAMEOVER_fontsize, RED);
        if(selected_deathmenu_option==1){
            DrawText("TRY AGAIN", 153, 372, TEXT_fontsize, RED);
            DrawText("GO TO MENU", 115, 442, TEXT_fontsize, WHITE);
            DrawText("QUIT", 284, 581, TEXT_fontsize, WHITE);
        }
        else if(selected_deathmenu_option==2){
            DrawText("TRY AGAIN", 153, 372, TEXT_fontsize, WHITE);
            DrawText("GO TO MENU", 115, 442, TEXT_fontsize, RED);
            DrawText("QUIT", 284, 581, TEXT_fontsize, WHITE);
        }
        else if(selected_deathmenu_option==3){
            DrawText("TRY AGAIN", 153, 372, TEXT_fontsize, WHITE);
            DrawText("GO TO MENU", 115, 442, TEXT_fontsize, WHITE);
            DrawText("QUIT", 284, 581, TEXT_fontsize, RED);
        }
        EndDrawing();
    }
    // After press ENTER key
    if(selected_deathmenu_option==1) return GAMEPLAY;
    if(selected_deathmenu_option==2) return MENU;
    if(selected_deathmenu_option==3) return QUIT;
}

// Gameplay work flow
int gameplay(int width, int height){

    // Circle
    int circle_x = width/3;
    int circle_y = height/3;
    int circle_radius = 25;

    // Circle edges
    int l_circle_x = circle_x - circle_radius;
    int r_circle_x = circle_x + circle_radius;
    int u_circle_y = circle_y - circle_radius;
    int b_circle_y = circle_y + circle_radius;

    // Axe coordinates
    int axe_x = 300;
    int axe_y = 0;
    int axe_length = 50;

    int direction = 10;

    // Axe edges
    int l_axe_x = axe_x;
    int r_axe_x = axe_x + axe_length;
    int u_axe_y = axe_y;
    int b_axe_y = axe_y + axe_length;

    bool collision_with_axe =
        (b_axe_y >= u_circle_y) &&
        (u_axe_y <= b_circle_y) &&
        (l_axe_x <= r_circle_x) &&
        (r_axe_x >= l_circle_x);

    while(!WindowShouldClose()){

        // Pause menu
        int pausemenu_option = 1;
        if(IsKeyReleased(KEY_BACKSPACE)){
            pausemenu_option = pause(width, height);
            if(pausemenu_option==RESUME);
            else if(pausemenu_option==MENU) return MENU;
            else if(pausemenu_option==QUIT) return QUIT;
        }

        BeginDrawing();
        ClearBackground(WHITE);

        if(collision_with_axe) return DEATH;

        else{

            // Update edges
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
            
            // Game work flow
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
        
        EndDrawing();
    }
}

// Game menu
int menu(int width, int height){
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
    if(selected_menu_option==1) return GAMEPLAY;
    if(selected_menu_option==2) return QUIT;
}

int main(void){
    // Game Window
    const int width = 1280;
    const int height = 720;
    InitWindow(width, height, "A Code Adventure");
    
    // Game FPS
    SetTargetFPS(60);
    
    // Main Variables
    int current_screen = MENU;
    
    // Loop game screen change
    while(current_screen!=QUIT){
        if(current_screen==MENU) current_screen = menu(width, height);
        else if(current_screen==GAMEPLAY) current_screen = gameplay(width, height);
        else if(current_screen==DEATH) current_screen = death(width, height);
    }
    
    // THE END
    CloseWindow();
    return 0;
}