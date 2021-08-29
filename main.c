#include "raylib.h"

#define MAX_SHOTS 5 
#define MAX_SHOTS_LEFT 5 

// Game screens
typedef enum{
    MENU,
    GAMEPLAY,
    RESUME,
    DEATH,
    QUIT,
}screen;


/* typedef struct{
    Vector2 speed; 
    bool active;
    Color color;
    Vector2 position;
    int lifespawn;
    float radius;
}shoot; */

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

// atirando para a direita 
typedef struct{
    Vector2 speed; 
    bool active;
    Color color;
    Vector2 position;
    int lifespawn;
    float radius;
}shoot;

// atirando para a esquerda
typedef struct{
    Vector2 speed_left; 
    bool active_left;
    Color color_left;
    Vector2 position_left;
    int lifespawn_left;
    float radius_left;
}shoot_left;

typedef struct{
    Rectangle rec;
}level_rec;

// Define functions
int menu(int width, int height);
int gameplay(int width, int height);
int pause(int width, int height);
int death(int width, int height);

// Gameplay work flow
int gameplay(int width, int height){
int windowDimensions[2];
    windowDimensions[0] = width; // x
    windowDimensions[1] = height; // y

    // acceleration due to gravity (pixels/s)/s
    float gravity = 0;
    float acceleration = 1.5;
    
    // num tiros
    shoot Shoot[MAX_SHOTS] = {0};
    shoot_left Shoot_left[MAX_SHOTS_LEFT] = {0};
    
    // direção projétil
    // bool shoot_right; // se 1, indo p/ direita, se 0, indo para a esquerda


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

    for(int i = 0; i < MAX_SHOTS; i++){ // no sé que se passa
            Shoot[i].position = (Vector2){scarfyData.pos.x + 30, scarfyData.pos.y + 30};
            Shoot[i].speed.x = 3;
            Shoot[i].radius = 10;
            Shoot[i].active = false;
            Shoot[i].color = BLUE;
            Shoot[i].lifespawn = 0;
    }

    for(int i = 0; i < MAX_SHOTS_LEFT; i++){ // no sé que se passa esquérdita
            Shoot_left[i].position_left = (Vector2){scarfyData.pos.x + 30, scarfyData.pos.y + 30};
            Shoot_left[i].speed_left.x = 3;
            Shoot_left[i].radius_left = 10;
            Shoot_left[i].active_left = false;
            Shoot_left[i].color_left = BLUE;
            Shoot_left[i].lifespawn_left = 0;
    }
    /* for(int i = 0; i < MAX_SHOTS; i++){
        shoot Shoot[i];
        
    } */
    int shoot_right = 0;

    
    while (!WindowShouldClose())
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangle(scarfyData.pos.x, scarfyData.pos.y, scarfyData.rec.width, scarfyData.rec.height, RED);
        // gravidade
        for(int i = 0; i < MAX_SHOTS; i++){
        }
        if(!isOnGround(scarfyData, windowDimensions[1])){
            scarfyData.pos.y += gravity;
        };

        // controles basicos 
        if (IsKeyDown(KEY_D))
        {
            shoot_right = 1;
            scarfyData.pos.x += 10;
        }
        if (IsKeyDown(KEY_A))
        {
            shoot_right = 0;
            scarfyData.pos.x -= 10;
        }
        if(IsKeyDown(KEY_W) && isOnGround(scarfyData, windowDimensions[1])){
            gravity -= 30;
            scarfyData.pos.y -= 1;

        }else if (IsKeyDown(KEY_W) && !isOnGround(scarfyData, windowDimensions[1]) && gravity >= 1)
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

        
        if (IsKeyPressed(KEY_SPACE) && shoot_right == 1)
        {
             for(int i = 0; i < MAX_SHOTS; i++){
                 if(!Shoot[i].active){
                     Shoot[i].position = (Vector2){scarfyData.pos.x + 30, scarfyData.pos.y + 30};
                     Shoot[i].active = true;
                     break;
                 }
             }
        }

        for(int i = 0; i < MAX_SHOTS; i++){
            if(Shoot[i].active){
                Shoot[i].position.x += 12;
                Shoot[i].lifespawn++;
                if(Shoot[i].position.x >= windowDimensions[0] + Shoot[i].radius){
                    Shoot[i].active = false;
                }
                if(Shoot[i].active){
                    DrawCircleV(Shoot[i].position, Shoot[i].radius, BLUE);
                }
                if(Shoot[i].lifespawn >= 800){
                    Shoot[i].position = (Vector2){scarfyData.pos.x + 30, scarfyData.pos.y + 30};
                    Shoot[i].speed = (Vector2){0, 0};
                    Shoot[i].lifespawn = 0;
                    Shoot[i].active = false;
                }
            }
        }
        if (IsKeyPressed(KEY_SPACE) && shoot_right == 0)
        {
             for(int i = 0; i < MAX_SHOTS_LEFT; i++){
                 if(!Shoot_left[i].active_left){
                     Shoot_left[i].position_left = (Vector2){scarfyData.pos.x + 30, scarfyData.pos.y + 30};
                     Shoot_left[i].active_left = true;
                     break;
                 }
             }
        }
        
        for(int i = 0; i < MAX_SHOTS_LEFT; i++){  
            if(Shoot_left[i].active_left){
                Shoot_left[i].position_left.x -= 12;
                Shoot_left[i].lifespawn_left++;
                if(Shoot_left[i].position_left.x <= 0 - Shoot[i].radius){
                    Shoot_left[i].active_left = false;
                }
                if(Shoot_left[i].active_left){
                    DrawCircleV(Shoot_left[i].position_left, Shoot_left[i].radius_left, BLUE);
                }
                if(Shoot_left[i].lifespawn_left >= 800){
                    Shoot_left[i].position_left = (Vector2){scarfyData.pos.x + 30, scarfyData.pos.y + 30};
                    Shoot_left[i].speed_left = (Vector2){0, 0};
                    Shoot_left[i].lifespawn_left = 0;
                    Shoot_left[i].active_left = false;
                }
            }

            // logica de colisões retangulos level design
            // primeiro rectangle teste
            level_rec primeiro;
            primeiro.rec.x = windowDimensions[0]/2 - primeiro.rec.x/2;
            primeiro.rec.y = windowDimensions[1] - primeiro.rec.height;  
            primeiro.rec.width = 150;
            primeiro.rec.height = 30;
            DrawRectangle(primeiro.rec.x, primeiro.rec.y, primeiro.rec.width, primeiro.rec.height, GREEN);
            /* if(CheckCollisionRecs(primeiro.rec, scarfyData.rec)){
                
            } */

        }

        // stop drawing
        EndDrawing();
    }
}

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