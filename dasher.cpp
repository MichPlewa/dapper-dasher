#include <raylib.h>

struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningtime;
};

int main(){
    const int windowWidth = 512;
    const int windowHeight = 380;

    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    const int gravity = 1000;
    const int jumpVal = -600;
    bool isInAir = false;

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowWidth / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningtime = 0.0;

    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimData nebulaData{
        {0.0, 0.0, nebula.width/8.f, nebula.height/8.f}, 
        {windowWidth, windowHeight - nebulaData.rec.height}, 
        0,
        1.0/12.0, 
        0.0
    };

    AnimData nebula2Data{
        {0.0, 0.0, nebula.width/8.f, nebula.height/8.f}, 
        {windowWidth + 300, windowHeight - nebulaData.rec.height}, 
        0, 
        1.0/16, 
        0.0
    };

    int nebulaVel = -200;
    int velosity = 0;

    SetTargetFPS(60);

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(WHITE);

        float dt = GetFrameTime();

        scarfyData.runningtime += dt;

        nebulaData.runningtime += dt;
        nebula2Data.runningtime += dt;

        if(scarfyData.pos.y >= windowHeight - scarfyData.rec.height){
            velosity = 0;
            isInAir = false;
            if(IsKeyPressed(KEY_SPACE)){
                velosity += jumpVal;
            }
        }else {
            isInAir = true;
            velosity += gravity * dt;
        }

        nebulaData.pos.x += nebulaVel * dt;

        if(nebulaData.runningtime >= nebulaData.updateTime){
            nebulaData.runningtime = 0.0;
            nebulaData.rec.x = nebulaData.frame * nebulaData.rec.width;
            nebulaData.frame++;
            if(nebulaData.frame > 7){
                nebulaData.frame = 0;
            }
        }

        nebula2Data.pos.x += nebulaVel * dt;

        if(nebula2Data.runningtime >= nebula2Data.updateTime){
            nebula2Data.runningtime = 0.0;
            nebula2Data.rec.x = nebula2Data.frame * nebula2Data.rec.width;
            nebula2Data.frame++;
            if(nebula2Data.frame > 7){
                nebula2Data.frame = 0;
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
        
        DrawTextureRec(nebula, nebulaData.rec, nebulaData.pos, WHITE);
        DrawTextureRec(nebula, nebula2Data.rec, nebula2Data.pos, RED);
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        EndDrawing();
    }

    UnloadTexture(nebula);
    UnloadTexture(scarfy);
    CloseWindow();
}