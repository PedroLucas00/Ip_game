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
    SUCCESS,
}screen;

typedef struct {
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
}AnimData;

bool isOnGround(AnimData playerData, int windowHeight) {return playerData.pos.y >= windowHeight - playerData.rec.height;}

// Running animation reference
/*animate(AnimData playerData, int initAnim, int endAnim,int currentFrame, int framesSpeed, int framesCounter) {
        initAnim = 0;
        endAnim = 4;

        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > endAnim || currentFrame < initAnim) currentFrame = initAnim;

            playerData.rec.x = (float)currentFrame*(float)playerData.rec.width;
        }
}*/

// atirando para a direita
typedef struct {
    Vector2 speed;
    bool active;
    Color color;
    Vector2 position;
    int lifespawn;
    float radius;
}shoot;

// atirando para a esquerda
typedef struct {
    Vector2 speed_left;
    bool active_left;
    Color color_left;
    Vector2 position_left;
    int lifespawn_left;
    float radius_left;
}shoot_left;

typedef struct {
    Rectangle rec;
}level_rec;

// Define functions
int menu(int width, int height);
int gameplay(int width, int height, int framesSpeed, int framesCounter);
int pause(int width, int height);
int death(int width, int height);
int success(int width, int height);

// Gameplay work flow
int gameplay(int width, int height, int framesSpeed, int framesCounter){
    // Starting audio device
    InitAudioDevice();
    // Define Gameplay Audio
    Sound gameplay_background_audio = LoadSound("audio/gameplay_background.wav");
    // Define Gameplay Background Image
    Texture2D gameplay_background = LoadTexture("images/gameplay_background.png");
    // Set Gameplay Volume
    SetSoundVolume(gameplay_background_audio, 0.4);
    // Play Gameplay Sound
    PlaySound(gameplay_background_audio);
    
    int windowDimensions[2];

    windowDimensions[0] = width; // x
    windowDimensions[1] = height; // y

    // variables to choose between animations intended
    int initAnim, endAnim;
    int currentFrame = 0;

    // acceleration due to gravity (pixels/s)/s
    float gravity = 0;
    float acceleration = 1.5;
    
    // num tiros
    shoot Shoot[MAX_SHOTS] = {0};
    shoot_left Shoot_left[MAX_SHOTS_LEFT] = {0};
    
    // direção projétil
    // bool shoot_right; // se 1, indo p/ direita, se 0, indo para a esquerda

    // Player Animation and variables
    Texture2D  player = LoadTexture("./Sprites/player_sheet.png");
    
    AnimData playerData;
    playerData.rec.width = (float)(player.width/19);
    playerData.rec.height = (float)player.height;
    playerData.rec.x = 0.0f;
    playerData.rec.y = 0.0f;
    playerData.pos.x = width/2 - playerData.rec.width/2;
    playerData.pos.y = height - playerData.rec.height;
    playerData.frame = 0;
    playerData.updateTime = 1.0/12.0;
    playerData.runningTime = 0.0;
    
    // Tiro animation and variables
    Texture2D  tiro = LoadTexture("./Sprites/malloc_sheet_upscale.png");

    AnimData tiroData;
    tiroData.rec.width = (float)(tiro.width/2);
    tiroData.rec.height = (float)tiro.height;
    tiroData.rec.x = 0.0f;
    tiroData.rec.y = 0.0f;
    tiroData.pos.x = width/2 - tiroData.rec.width/2;
    tiroData.pos.y = height - tiroData.rec.height;
    tiroData.frame = 0;
    tiroData.updateTime = 1.0/12.0;
    tiroData.runningTime = 0.0;

    // Memory animation and variables
    Texture2D  memory = LoadTexture("./Sprites/memory_sheet.png");

    AnimData memoryData;
    memoryData.rec.width = (float)(memory.width/7);
    memoryData.rec.height = (float)memory.height;
    memoryData.rec.x = 0.0f;
    memoryData.rec.y = 0.0f;
    memoryData.pos.x = 1120;
    memoryData.pos.y = 0;
    memoryData.frame = 0;
    memoryData.updateTime = 1.0/12.0;
    memoryData.runningTime = 0.0;

    // Memory animation and variables
    Texture2D  ACM = LoadTexture("./Sprites/ACM_sheet_upscale.png");

    AnimData ACMData;
    ACMData.rec.width = (float)(ACM.width/9); 
    ACMData.rec.height = (float)ACM.height;
    ACMData.rec.x = 0.0f;
    ACMData.rec.y = 0.0f;
    ACMData.pos.x = 1060;
    ACMData.pos.y = 40;
    ACMData.frame = 0;
    ACMData.updateTime = 1.0/12.0;
    ACMData.runningTime = 0.0;

    // platform sprite texture
    Texture2D  platform = LoadTexture("./Sprites/sand_platform.png");

    level_rec prim;

    for(int i = 0; i < MAX_SHOTS; i++){ // no sé que se passa
        Shoot[i].position = (Vector2){playerData.pos.x + 30, playerData.pos.y + 30};
        Shoot[i].speed.x = 3;
        Shoot[i].radius = 10;
        Shoot[i].active = false;
        Shoot[i].color = BLUE;
        Shoot[i].lifespawn = 0;
    }

    for(int i = 0; i < MAX_SHOTS_LEFT; i++){ // no sé que se passa esquérdita
        Shoot_left[i].position_left = (Vector2){playerData.pos.x + 30, playerData.pos.y + 30};
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
    
    //Rectangle floor = (FloorX, FloorY, FloorW, FloorH);
    
    while (!WindowShouldClose()){

        // Pause menu
        int pausemenu_option = 1;
        if(IsKeyReleased(KEY_BACKSPACE)){
            PauseSound(gameplay_background_audio);
            pausemenu_option = pause(width, height);
            if(pausemenu_option==RESUME) ResumeSound(gameplay_background_audio);
            else if(pausemenu_option==MENU) return MENU;
            else if(pausemenu_option==QUIT) return QUIT;
        }

        // Frame counter for animation incrementation
        framesCounter++;

        // gravidade
        Rectangle foot = {playerData.pos.x, playerData.pos.y, playerData.rec.width, playerData.rec.height};

        // PLATFORM RECTANGLES
        Rectangle BluePlatform = {windowDimensions[0]/2 - 25, windowDimensions[1] - 50, 50, 50};
        Rectangle YellowPlatform = {windowDimensions[0]/2 + 120, windowDimensions[1] - 220, 125, 50};
        Rectangle ThirdPlatform = {windowDimensions[0]/2 - 150, windowDimensions[1] - 290, 125, 50};
        

        if(playerData.pos.y <= -1){
            playerData.pos.y = 0;
        }
        if(playerData.pos.x <= 0){
            playerData.pos.x = 0;
        }
        if(playerData.pos.x >= windowDimensions[0]){
            playerData.pos.x = windowDimensions[0];
        }

        for(int i = 0; i < MAX_SHOTS; i++){
        }

        if(!isOnGround(playerData, windowDimensions[1])){
            playerData.pos.y += gravity;
        }
        
        if(CheckCollisionRecs(foot, BluePlatform)){
            playerData.pos.y = windowDimensions[1] - BluePlatform.height - playerData.rec.height - 1;
            acceleration = 0;
            gravity = 0;
        }
        
        if(CheckCollisionRecs(foot, YellowPlatform)){
            playerData.pos.y = YellowPlatform.y - playerData.rec.height - 1;
            acceleration = 0;
            gravity = 0;
        }
        if(CheckCollisionRecs(foot, ThirdPlatform)){
            
            playerData.pos.y = ThirdPlatform.y - playerData.rec.height - 1;
            acceleration = 0;
            gravity = 0; 

        }

        // controles basicos 
        if (IsKeyDown(KEY_D)){
            initAnim = 0;
            endAnim = 4;
            shoot_right = 1;
            playerData.pos.x += 10;
            
            if (framesCounter >= (60/framesSpeed)){
                framesCounter = 0;
                currentFrame++;
                
                if (currentFrame > endAnim || currentFrame < initAnim) currentFrame = initAnim;

                playerData.rec.x = (float)currentFrame*(float)playerData.rec.width;
            }
        }
        
        if (IsKeyDown(KEY_A)){
            initAnim = 11;
            endAnim = 15;
            
            if (framesCounter >= (60/framesSpeed)){
                framesCounter = 0;
                currentFrame++;
                
                if (currentFrame > endAnim || currentFrame < initAnim) currentFrame = initAnim;
                
                playerData.rec.x = (float)currentFrame*(float)playerData.rec.width;
            }
            
            shoot_right = 0;
            playerData.pos.x -= 10;
        }
        if(IsKeyDown(KEY_W) && ((isOnGround(playerData, windowDimensions[1]) || CheckCollisionRecs(foot, YellowPlatform) || CheckCollisionRecs(foot, BluePlatform) || CheckCollisionRecs(foot, ThirdPlatform)))){
            gravity -= 30;
            playerData.pos.y -= 1;
            
            if(shoot_right){
                initAnim = 6;
                endAnim = 6;
                playerData.rec.x = 6*(float)playerData.rec.width;
            }
            
            if(!shoot_right){
                initAnim = 8;
                endAnim = 8;
                playerData.rec.x = 8*(float)playerData.rec.width;
            }
        }else if (IsKeyDown(KEY_W) && (!isOnGround(playerData, windowDimensions[1]) || !CheckCollisionRecs(foot, YellowPlatform) || !CheckCollisionRecs(foot, BluePlatform) || !CheckCollisionRecs(foot, ThirdPlatform)) && gravity >= 1)
        {
            acceleration = 0.18;
        }else{
            if(!isOnGround(playerData, windowDimensions[1]) && !CheckCollisionRecs(foot, YellowPlatform) && !CheckCollisionRecs(foot, BluePlatform) && !CheckCollisionRecs(foot, ThirdPlatform))
            acceleration = 1.5;
        }
        if(isOnGround(playerData, windowDimensions[1]) && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)){
            playerData.pos.y = windowDimensions[1] - playerData.rec.height;
            gravity = 1;

            if (shoot_right) {
            initAnim = 0;
            endAnim = 0;
            playerData.rec.x = 0*(float)playerData.rec.width;
            }

            if (!shoot_right) {
            initAnim = 11;
            endAnim = 11;
            playerData.rec.x = 11*(float)playerData.rec.width;
            }
        }
        
        gravity += acceleration;
        
        // Tiro do player
        if (IsKeyPressed(KEY_SPACE) && shoot_right == 1)
        {
            for(int i = 0; i < MAX_SHOTS; i++){
                if(!Shoot[i].active){
                    Shoot[i].position = (Vector2){playerData.pos.x + 30, playerData.pos.y + 30};
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
                    Shoot[i].position = (Vector2){playerData.pos.x + 30, playerData.pos.y + 30};
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
                    Shoot_left[i].position_left = (Vector2){playerData.pos.x + 30, playerData.pos.y + 30};
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
                    Shoot_left[i].position_left = (Vector2){playerData.pos.x + 30, playerData.pos.y + 30};
                    Shoot_left[i].speed_left = (Vector2){0, 0};
                    Shoot_left[i].lifespawn_left = 0;
                    Shoot_left[i].active_left = false;
                }
            }
        }

        // memory and ACM animation
        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 1 || currentFrame < 0) currentFrame = 0;

            memoryData.rec.x = (float)currentFrame*(float)memoryData.rec.width;
            ACMData.rec.x = (float)currentFrame*(float)ACMData.rec.width;
        }

        /* bool platformCollision = CheckCollisionRecs(foot, BluePlatform);
        bool onFloor = CheckCollisionRecs(foot, floor);  */        
        /* if(onFloor){
            playerData.pos.y = windowDimensions[1] + playerData.rec.y;
        } */
        
        // Gameplay Drawing
        BeginDrawing();
        DrawTexture(gameplay_background, 0, 0, WHITE);

        DrawTextureRec(
            player,
            playerData.rec,
            playerData.pos,
            WHITE);
        
        DrawTextureRec(
            memory,
            memoryData.rec,
            memoryData.pos,
            WHITE);

        DrawTextureRec(
            ACM,
            ACMData.rec,
            ACMData.pos,
            WHITE);
        
        DrawRectangle(BluePlatform.x, BluePlatform.y, BluePlatform.width, BluePlatform.height, BLUE);
        DrawRectangle(YellowPlatform.x, YellowPlatform.y, YellowPlatform.width, YellowPlatform.height, YELLOW);
        DrawRectangle(ThirdPlatform.x, ThirdPlatform.y, ThirdPlatform.width, ThirdPlatform.height, PURPLE);

        EndDrawing();
        
        // Shortcut to transition between screens
        if(IsKeyReleased(KEY_O)||IsKeyReleased(KEY_P)) UnloadSound(gameplay_background_audio);
        if(IsKeyReleased(KEY_O)) return DEATH;
        if(IsKeyReleased(KEY_P)) return SUCCESS;
        
        // Check if the background sound is playing
        if(!IsSoundPlaying(gameplay_background_audio)) PlaySound(gameplay_background_audio);
    }
}

// Success screen
int success(int width, int height){
    // Success Menu Variables
    int selected_successmenu_option = 1;
    // Success Menu Options Positions
    Vector2 PLAY_AGAIN_position = {886, 372}, GO_TO_MENU_position = {886, 442}, QUIT_position = {886, 581}, VICTORY_position = {22, height-(height/6)};
    // Define VICTORY font size
    int VICTORY_fontsize = 120;
    // Define text font size
    int TEXT_fontsize = 60;
    // Starting audio device
    InitAudioDevice();
    // Define Success Menu Audio
    Sound menu_selecting_audio = LoadSound("audio/menu_selecting.wav");
    Sound menu_confirm_audio = LoadSound("audio/menu_confirm.wav");
    Sound menu_return_audio = LoadSound("audio/menu_return.wav");
    Sound menu_background_audio = LoadSound("audio/menu_background_audio.wav");
    Sound success_audio = LoadSound("audio/success_audio.mp3");
    // Define Text Font
    Font successmenu_font = LoadFontEx("fonts/Oswald-SemiBold.ttf", TEXT_fontsize, 0, 0);
    Font VICTORY_font = LoadFontEx("fonts/Oswald-Bold.ttf", VICTORY_fontsize, 0, 0);
    // Define Success Background Image
    Texture2D success_background = LoadTexture("images/success_background.png");
    // Set Success Menu Volume
    SetSoundVolume(menu_selecting_audio, 0.8);
    SetSoundVolume(menu_confirm_audio, 0.8);
    SetSoundVolume(menu_return_audio, 0.8);
    SetSoundVolume(menu_background_audio, 0.4);
    SetSoundVolume(success_audio, 0.5);
    // Play Start Menu Sound
    PlaySound(menu_selecting_audio);
    PlaySound(success_audio);
    // Loop while waiting for a ENTER press
    while(!IsKeyReleased(KEY_ENTER)){
        // Menu Work Flow
        if(selected_successmenu_option==4) selected_successmenu_option = 1;
        if(selected_successmenu_option==0) selected_successmenu_option = 3;
        if(IsKeyReleased(KEY_UP)||IsKeyReleased(KEY_DOWN)) PlaySound(menu_selecting_audio);
        if(IsKeyReleased(KEY_UP)) selected_successmenu_option--;
        if(IsKeyReleased(KEY_DOWN)) selected_successmenu_option++;
        // Menu Drawing
        BeginDrawing();
        DrawTexture(success_background, 0, 0, WHITE);
        DrawTextEx(VICTORY_font, "VICTORY", VICTORY_position, VICTORY_fontsize, 5, RED);
        if(selected_successmenu_option==1){
            DrawTextEx(successmenu_font, "PLAY AGAIN", PLAY_AGAIN_position, TEXT_fontsize, 5, RED);
            DrawTextEx(successmenu_font, "GO TO MENU", GO_TO_MENU_position, TEXT_fontsize, 5, WHITE);
            DrawTextEx(successmenu_font, "QUIT", QUIT_position, TEXT_fontsize, 5, WHITE);
        }
        else if(selected_successmenu_option==2){
            DrawTextEx(successmenu_font, "PLAY AGAIN", PLAY_AGAIN_position, TEXT_fontsize, 5, WHITE);
            DrawTextEx(successmenu_font, "GO TO MENU", GO_TO_MENU_position, TEXT_fontsize, 5, RED);
            DrawTextEx(successmenu_font, "QUIT", QUIT_position, TEXT_fontsize, 5, WHITE);
        }
        else if(selected_successmenu_option==3){
            DrawTextEx(successmenu_font, "PLAY AGAIN", PLAY_AGAIN_position, TEXT_fontsize, 5, WHITE);
            DrawTextEx(successmenu_font, "GO TO MENU", GO_TO_MENU_position, TEXT_fontsize, 5, WHITE);
            DrawTextEx(successmenu_font, "QUIT", QUIT_position, TEXT_fontsize, 5, RED);
        }
        EndDrawing();

        // Check if the background sound is playing
        if(!IsSoundPlaying(menu_background_audio)) PlaySound(menu_background_audio);
    }

    // Ending Death Menu Background Audio
    UnloadSound(menu_background_audio);
    UnloadSound(success_audio);
    
    // After press ENTER key
    if(selected_successmenu_option==1){
        PlaySound(menu_confirm_audio);
        return GAMEPLAY;
    }
    if(selected_successmenu_option==2){
        PlaySound(menu_return_audio);
        return MENU;
    }
    if(selected_successmenu_option==3) return QUIT;

    // Ending audio device
    UnloadSound(menu_selecting_audio);
    UnloadSound(menu_confirm_audio);
    UnloadSound(menu_return_audio);
    CloseAudioDevice();
}

// Pause menu
int pause(int width, int height){
    // Pause Menu Variables
    int selected_pausemenu_option = 1;
    // Pause Menu Options Positions
    Vector2 RESUME_position = {563, 256}, GO_TO_MENU_position = {519, 328}, QUIT_position = {594, 399};
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
        DrawTexture(pause_background, 415, 217, WHITE);
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
    
    // Animation aux
    int framesSpeed = 6;
    int framesCounter = 0;
    
    // Player Animation
    
    // Game FPS
    SetTargetFPS(60);
    
    // Main Variables
    int current_screen = MENU;
    
    // Loop game screen change
    while(current_screen!=QUIT){
        if(current_screen==MENU) current_screen = menu(width, height);
        else if(current_screen==GAMEPLAY) current_screen = gameplay(width, height, framesSpeed, framesCounter);
        else if(current_screen==DEATH) current_screen = death(width, height);
        else if(current_screen==SUCCESS) current_screen = success(width, height);
    }
    
    // THE END
    CloseWindow();
    return 0;
}