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
    // Pause Menu Options Positions
    Vector2 RESUME_position = {566, 268}, GO_TO_MENU_position = {522, 339}, QUIT_position = {600, 411};
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
        DrawTexture(pause_background, 416, 218, WHITE);
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
    Vector2 TRY_AGAIN_position = {188, 372}, GO_TO_MENU_position = {153, 442}, QUIT_position = {303, 581}, GAMEOVER_position = {width-(width/3)-(width/120), height-(height/6)};
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