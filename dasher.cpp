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
    AnimData nebulaData{
        {0.0, 0.0, nebula.width/8.f, nebula.height/8.f}, 
        {windowDimensions[0], windowDimensions[1] - nebulaData.rec.height}, 
        0,
        1.0/12.0, 
        0.0
    };

    AnimData nebula2Data{
        {0.0, 0.0, nebula.width/8.f, nebula.height/8.f}, 
        {windowDimensions[0] + 300, windowDimensions[1] - nebulaData.rec.height}, 
        0, 
        1.0/16, 
        0.0
    };

    AnimData nebulae[2]{ nebulaData, nebula2Data };

    int nebulaVel = -200;
    int velosity = 0;

    SetTargetFPS(60);

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(WHITE);

        float dt = GetFrameTime();

        scarfyData.runningtime += dt;

        nebulae[0].runningtime += dt;
        nebulae[1].runningtime += dt;

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

        nebulae[0].pos.x += nebulaVel * dt;

        if(nebulae[0].runningtime >= nebulae[0].updateTime){
            nebulae[0].runningtime = 0.0;
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            if(nebulae[0].frame > 7){
                nebulae[0].frame = 0;
            }
        }

        nebulae[1].pos.x += nebulaVel * dt;

        if(nebulae[1].runningtime >= nebulae[1].updateTime){
            nebulae[1].runningtime = 0.0;
            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;
            if(nebulae[1].frame > 7){
                nebulae[1].frame = 0;
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
        
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        EndDrawing();
    }
    

    UnloadTexture(nebula);
    UnloadTexture(scarfy);
    CloseWindow();
}