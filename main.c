#include "raylib.h"

<<<<<<< Updated upstream
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


int main()
{
    // array with window dimensions
    int windowDimensions[2];
    windowDimensions[0] = 1280; // x
    windowDimensions[1] = 720; // y

    // initialize the window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");

    // acceleration due to gravity (pixels/s)/s
    int gravity = 0;
    int acceleration = 1.5;
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

    
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        gravity += acceleration;
        // start drawing
=======
// Define functions
void menu(int width, int height);
void gameplay(int width, int height);

void gameplay(int width, int height){
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

    while(!WindowShouldClose()){
>>>>>>> Stashed changes
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
        if(IsKeyPressed(KEY_SPACE) && isOnGround(scarfyData, windowDimensions[1])){
            gravity -= 30;
            scarfyData.pos.y -= 1;

        }else if (IsKeyDown(KEY_SPACE) && !isOnGround(scarfyData, windowDimensions[1]) && gravity >= 0)
        {
            acceleration = 0.25;
        }else{
            if(!isOnGround(scarfyData, windowDimensions[1]))
            acceleration = 1.5;
        }
        if(isOnGround(scarfyData, windowDimensions[1])){
            scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
            gravity = 1;
        } 
        // stop drawing
        EndDrawing();
    }
<<<<<<< Updated upstream
     
=======
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
    // Game Window
    const int width = 1280;
    const int height = 720;
    InitWindow(width, height, "A Code Adventure");
    
    // Game FPS
    SetTargetFPS(60);
    
    // Menu
    menu(width, height);
    
    // THE END
>>>>>>> Stashed changes
    CloseWindow();
}