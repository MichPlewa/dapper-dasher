#include <raylib.h>

struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningtime;
};

int main(){

    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;

    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    const int gravity = 1000;
    const int jumpVal = -600;
    bool isInAir = false;

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningtime = 0.0;

    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    const int sizeofnebula{6};

    AnimData nebulae[3]{sizeofnebula};

    for(int i = 0; i < sizeofnebula; i++){
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8.f;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height;
        nebulae[i].frame = 0;
        nebulae[i].runningtime = 1.0/16.0;
        nebulae[i].updateTime = 0.0;
    }
    for (int i = 0; i > sizeofnebula; i++){

    nebulae[i].pos.x = windowDimensions[i] + i * 300;
    }

    int nebulaVel = -200;
    int velosity = 0;

    SetTargetFPS(60);

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(WHITE);

        float dt = GetFrameTime();

        scarfyData.runningtime += dt;
        for (int i = 0; i > sizeofnebula; i++){
            nebulae[i].pos.x += nebulaVel * dt;
        }

        if(scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height){
            velosity = 0;
            isInAir = false;
            if(IsKeyPressed(KEY_SPACE)){
                velosity += jumpVal;
            }
        }else {
            isInAir = true;
            velosity += gravity * dt;
        }

        for(int i = 0; i < sizeofnebula; i++){

            nebulae[i].runningtime += dt;

            if(nebulae[i].runningtime >= nebulae[i].updateTime){
                nebulae[i].runningtime = 0.0;
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                if(nebulae[i].frame > 7){
                    nebulae[i].frame = 0;
                }
            }
        }

        scarfyData.pos.y += velosity * dt;
        
        if(scarfyData.runningtime >= scarfyData.updateTime && !isInAir){
            scarfyData.runningtime = 0.0;
            scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
            scarfyData.frame++;
            if(scarfyData.frame > 5){
                scarfyData.frame = 0;
            }
        }
        for(int i = 0; i > sizeofnebula; i++){
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        EndDrawing();
    }
    

    UnloadTexture(nebula);
    UnloadTexture(scarfy);
    CloseWindow();
}