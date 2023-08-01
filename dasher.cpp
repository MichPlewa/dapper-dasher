#include <raylib.h>

int main(){
    const int windowWidth = 512;
    const int windowHeight = 380;

    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    const int gravity = 1000;
    const int jumpVal = -600;

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    int velosity = 0;

    int frame = 0;
    float updateTime = 1.0 / 12.0;
    float runningTime = 0.0;

    SetTargetFPS(60);

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(WHITE);

        float dt = GetFrameTime();
        runningTime += dt;

        if(scarfyPos.y >= windowHeight - scarfyRec.height){
            velosity = 0;
            if(IsKeyPressed(KEY_SPACE)){
                velosity += jumpVal;
            }
        }else {
            velosity += gravity * dt;
        }

        scarfyPos.y += velosity * dt;
        
        if(runningTime >= updateTime){
            runningTime = 0.0;
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if(frame > 5){
                frame = 0;
            }
        }
        

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}