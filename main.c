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

    // Player Animation
    Texture2D  player = LoadTexture("./Sprites/player_sheet.png");
    float frameWidth = (float)(player.width/19);  
    float timer = 0.0f;
    // player variables
    AnimData scarfyData;
    scarfyData.rec.width = frameWidth;
    scarfyData.rec.height = (float)player.height;
    scarfyData.rec.x = 1;
    scarfyData.rec.y = 1;
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
        DrawTextureRec(
            player,
            scarfyData.rec,
            scarfyData.pos,
            RAYWHITE);
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
        }

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


// Pause menu
int pause(int width, int height){
    // Pause Menu Variables
    int selected_pausemenu_option = 1;
    // Pause Menu Options Positions
    Vector2 RESUME_position = {563, 244}, GO_TO_MENU_position = {519, 315}, QUIT_position = {594, 387};
    // Define text font size
    int TEXT_fontsize = 60;
    // Starting audio device
    InitAudioDevice();
    // Define Pause Menu Audio
    Sound menu_selecting_audio = LoadSound("audio/menu_selecting.wav");
    Sound menu_confirm_audio = LoadSound("audio/menu_confirm.wav");
    Sound menu_return_audio = LoadSound("audio/menu_return.wav");
    Sound pausemenu_background_audio = LoadSound("audio/pausemenu_background_audio.wav");
    // Define Text Font
    Font pausemenu_font = LoadFontEx("fonts/Oswald-SemiBold.ttf", TEXT_fontsize, 0, 0);
    // Define Pause Background Image
    Texture2D pause_background = LoadTexture("images/pause_menu_background.png");
    // Set Pause Menu Volume
    SetSoundVolume(menu_selecting_audio, 0.8);
    SetSoundVolume(menu_confirm_audio, 0.8);
    SetSoundVolume(menu_return_audio, 0.8);
    SetSoundVolume(pausemenu_background_audio, 0.4);
    // Play Start Pause Menu Sound
    PlaySound(menu_selecting_audio);
    // Loop while waiting for a ENTER press
    while(!IsKeyReleased(KEY_ENTER)){
        // Menu Work Flow
        if(selected_pausemenu_option==4) selected_pausemenu_option = 1;
        if(selected_pausemenu_option==0) selected_pausemenu_option = 3;
        if(IsKeyReleased(KEY_UP)||IsKeyReleased(KEY_DOWN)) PlaySound(menu_selecting_audio);
        if(IsKeyReleased(KEY_UP)) selected_pausemenu_option--;
        if(IsKeyReleased(KEY_DOWN)) selected_pausemenu_option++;
        // Menu Drawing
        BeginDrawing();
        DrawTexture(pause_background, 415, 205, WHITE);
        if(selected_pausemenu_option==1){
            DrawTextEx(pausemenu_font, "RESUME", RESUME_position, TEXT_fontsize, 5, RED);
            DrawTextEx(pausemenu_font, "GO TO MENU", GO_TO_MENU_position, TEXT_fontsize, 5, WHITE);
            DrawTextEx(pausemenu_font, "QUIT", QUIT_position, TEXT_fontsize, 5, WHITE);
        }
        else if(selected_pausemenu_option==2){
            DrawTextEx(pausemenu_font, "RESUME", RESUME_position, TEXT_fontsize, 5, WHITE);
            DrawTextEx(pausemenu_font, "GO TO MENU", GO_TO_MENU_position, TEXT_fontsize, 5, RED);
            DrawTextEx(pausemenu_font, "QUIT", QUIT_position, TEXT_fontsize, 5, WHITE);
        }
        else if(selected_pausemenu_option==3){
            DrawTextEx(pausemenu_font, "RESUME", RESUME_position, TEXT_fontsize, 5, WHITE);
            DrawTextEx(pausemenu_font, "GO TO MENU", GO_TO_MENU_position, TEXT_fontsize, 5, WHITE);
            DrawTextEx(pausemenu_font, "QUIT", QUIT_position, TEXT_fontsize, 5, RED);
        }
        EndDrawing();

        // Check if the background sound is playing
        if(!IsSoundPlaying(pausemenu_background_audio)) PlaySound(pausemenu_background_audio);
    }

    // Ending Death Menu Background Audio
    UnloadSound(pausemenu_background_audio);

    // After press ENTER key
    if(selected_pausemenu_option==1){
        PlaySound(menu_confirm_audio);
        return RESUME;
    }
    if(selected_pausemenu_option==2){
        PlaySound(menu_return_audio);
        return MENU;
    }
    if(selected_pausemenu_option==3) return QUIT;

    // Ending audio device
    UnloadSound(menu_selecting_audio);
    UnloadSound(menu_confirm_audio);
    UnloadSound(menu_return_audio);
    CloseAudioDevice();
}

// Death menu
int death(int width, int height){
    // Death Menu Variables
    int selected_deathmenu_option = 1;
    // Death Menu Options Positions
    Vector2 TRY_AGAIN_position = {188, 372}, GO_TO_MENU_position = {153, 442}, QUIT_position = {303, 581}, GAMEOVER_position = {width-(width/3)-(width/120)-3, height-(height/6)};
    // Define GAMEOVER font size
    int GAMEOVER_fontsize = 120;
    // Define text font size
    int TEXT_fontsize = 60;
    // Starting audio device
    InitAudioDevice();
    // Define Death Menu Audio
    Sound menu_selecting_audio = LoadSound("audio/menu_selecting.wav");
    Sound menu_confirm_audio = LoadSound("audio/menu_confirm.wav");
    Sound menu_return_audio = LoadSound("audio/menu_return.wav");
    Sound deathmenu_background_audio = LoadSound("audio/deathmenu_background_audio.wav");
    // Define Text Font
    Font deathmenu_font = LoadFontEx("fonts/Oswald-SemiBold.ttf", TEXT_fontsize, 0, 0);
    Font GAMEOVER_font = LoadFontEx("fonts/Oswald-Bold.ttf", GAMEOVER_fontsize, 0, 0);
    // Define Death Background Image
    Texture2D death_background = LoadTexture("images/death_background.png");
    // Set Death Menu Volume
    SetSoundVolume(menu_selecting_audio, 0.8);
    SetSoundVolume(menu_confirm_audio, 0.8);
    SetSoundVolume(menu_return_audio, 0.8);
    SetSoundVolume(deathmenu_background_audio, 0.4);
    // Play Start Menu Sound
    PlaySound(menu_selecting_audio);
    // Loop while waiting for a ENTER press
    while(!IsKeyReleased(KEY_ENTER)){
        // Menu Work Flow
        if(selected_deathmenu_option==4) selected_deathmenu_option = 1;
        if(selected_deathmenu_option==0) selected_deathmenu_option = 3;
        if(IsKeyReleased(KEY_UP)||IsKeyReleased(KEY_DOWN)) PlaySound(menu_selecting_audio);
        if(IsKeyReleased(KEY_UP)) selected_deathmenu_option--;
        if(IsKeyReleased(KEY_DOWN)) selected_deathmenu_option++;
        // Menu Drawing
        BeginDrawing();
        DrawTexture(death_background, 0, 0, WHITE);
        DrawTextEx(GAMEOVER_font, "GAME OVER", GAMEOVER_position, GAMEOVER_fontsize, 5, RED);
        if(selected_deathmenu_option==1){
            DrawTextEx(deathmenu_font, "TRY AGAIN", TRY_AGAIN_position, TEXT_fontsize, 5, RED);
            DrawTextEx(deathmenu_font, "GO TO MENU", GO_TO_MENU_position, TEXT_fontsize, 5, WHITE);
            DrawTextEx(deathmenu_font, "QUIT", QUIT_position, TEXT_fontsize, 5, WHITE);
        }
        else if(selected_deathmenu_option==2){
            DrawTextEx(deathmenu_font, "TRY AGAIN", TRY_AGAIN_position, TEXT_fontsize, 5, WHITE);
            DrawTextEx(deathmenu_font, "GO TO MENU", GO_TO_MENU_position, TEXT_fontsize, 5, RED);
            DrawTextEx(deathmenu_font, "QUIT", QUIT_position, TEXT_fontsize, 5, WHITE);
        }
        else if(selected_deathmenu_option==3){
            DrawTextEx(deathmenu_font, "TRY AGAIN", TRY_AGAIN_position, TEXT_fontsize, 5, WHITE);
            DrawTextEx(deathmenu_font, "GO TO MENU", GO_TO_MENU_position, TEXT_fontsize, 5, WHITE);
            DrawTextEx(deathmenu_font, "QUIT", QUIT_position, TEXT_fontsize, 5, RED);
        }
        EndDrawing();

        // Check if the background sound is playing
        if(!IsSoundPlaying(deathmenu_background_audio)) PlaySound(deathmenu_background_audio);
    }

    // Ending Death Menu Background Audio
    UnloadSound(deathmenu_background_audio);
    
    // After press ENTER key
    if(selected_deathmenu_option==1){
        PlaySound(menu_confirm_audio);
        return GAMEPLAY;
    }
    if(selected_deathmenu_option==2){
        PlaySound(menu_return_audio);
        return MENU;
    }
    if(selected_deathmenu_option==3) return QUIT;

    // Ending audio device
    UnloadSound(menu_selecting_audio);
    UnloadSound(menu_confirm_audio);
    UnloadSound(menu_return_audio);
    CloseAudioDevice();
}

// Game menu
int menu(int width, int height){
    // Menu Variables
    int selected_menu_option = 1;
    // Menu Options Positions
    Vector2 PLAY_position = {299, 372}, QUIT_position = {303, 581};
    // Define text font size
    int TEXT_fontsize = 60;
    // Starting audio device
    InitAudioDevice();
    // Define Menu Audio
    Sound menu_selecting_audio = LoadSound("audio/menu_selecting.wav");
    Sound menu_confirm_audio = LoadSound("audio/menu_confirm.wav");
    Sound menu_return_audio = LoadSound("audio/menu_return.wav");
    Sound menu_background_audio = LoadSound("audio/menu_background_audio.wav");
    // Define Text Font
    Font menu_font = LoadFontEx("fonts/Oswald-SemiBold.ttf", TEXT_fontsize, 0, 0);
    // Define Menu Background Image
    Texture2D menu_background = LoadTexture("images/menu_background.png");
    // Set Menu Volume
    SetSoundVolume(menu_selecting_audio, 0.8);
    SetSoundVolume(menu_confirm_audio, 0.8);
    SetSoundVolume(menu_return_audio, 0.8);
    SetSoundVolume(menu_background_audio, 0.4);
    // Play Start Menu Sound
    PlaySound(menu_selecting_audio);
    // Loop while waiting for a ENTER press
    while(!IsKeyDown(KEY_ENTER)){
        // Menu Work Flow
        if(selected_menu_option==3) selected_menu_option = 1;
        if(selected_menu_option==0) selected_menu_option = 2;
        if(IsKeyReleased(KEY_UP)||IsKeyReleased(KEY_DOWN)) PlaySound(menu_selecting_audio);
        if(IsKeyReleased(KEY_UP)) selected_menu_option--;
        if(IsKeyReleased(KEY_DOWN)) selected_menu_option++;
        // Menu Drawing
        BeginDrawing();
        DrawTexture(menu_background, 0, 0, WHITE);
        if(selected_menu_option==1){
            DrawTextEx(menu_font, "PLAY", PLAY_position, TEXT_fontsize, 5, RED);
            DrawTextEx(menu_font, "QUIT", QUIT_position, TEXT_fontsize, 5, WHITE);
        }
        else if(selected_menu_option==2){
            DrawTextEx(menu_font, "PLAY", PLAY_position, TEXT_fontsize, 5, WHITE);
            DrawTextEx(menu_font, "QUIT", QUIT_position, TEXT_fontsize, 5, RED);
        }
        EndDrawing();

        // Check if the background sound is playing
        if(!IsSoundPlaying(menu_background_audio)) PlaySound(menu_background_audio);
    }

    // Ending Menu Background Audio
    UnloadSound(menu_background_audio);

    // After press ENTER key
    if(selected_menu_option==1){
        PlaySound(menu_confirm_audio);
        return GAMEPLAY;
    }
    if(selected_menu_option==2) return QUIT;

    // Ending audio device
    UnloadSound(menu_selecting_audio);
    UnloadSound(menu_confirm_audio);
    UnloadSound(menu_return_audio);
    CloseAudioDevice();
}

int main(void){
    // Game Window
    const int width = 1280;
    const int height = 720;
    InitWindow(width, height, "A Code Adventure");

    // Game Window Icon
    Image game_icon = LoadImage("images/game_icon.png");
    SetWindowIcon(game_icon);
    
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