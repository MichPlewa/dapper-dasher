#include <raylib.h>

int main(){
    const int windowWidth = 512;
    const int windowHeight = 380;

    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    const int gravity = 1000;
    const int jumpVal = -600;
    bool isInAir = false;

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec{};
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRec{0.0, 0.0, nebula.width/8.f, nebula.height/8.f};
    Vector2 nebulaPos{windowWidth, windowHeight - nebulaRec.height};

    int nebulaVel = -200;

    int velosity = 0;

    int frame = 0;
    float updateTime = 1.0 / 12.0;
    float runningTime = 0;

    int nebFrame = 0;
    const float nebUpdateTime = 1.0/12.0;
    float nebRunningTime = 0;

    SetTargetFPS(60);

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(WHITE);

        float dt = GetFrameTime();

        runningTime += dt;

        nebRunningTime += dt;

        if(scarfyPos.y >= windowHeight - scarfyRec.height){
            velosity = 0;
            isInAir = false;
            if(IsKeyPressed(KEY_SPACE)){
                velosity += jumpVal;
            }
        }else {
            isInAir = true;
            velosity += gravity * dt;
        }

        nebulaPos.x += nebulaVel * dt;

        if(nebRunningTime >= nebUpdateTime){
            nebRunningTime = 0.0;
            nebulaRec.x = nebFrame * nebulaRec.width;
            nebFrame++;
            if(nebFrame > 7){
                nebFrame = 0;
            }
        }

        scarfyPos.y += velosity * dt;
        
        if(runningTime >= updateTime && !isInAir){
            runningTime = 0.0;
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if(frame > 5){
                frame = 0;
            }
        }
        
        DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(nebula);
    UnloadTexture(scarfy);
    CloseWindow();
}