#include <raylib.h>

int main(){
    const int windowWidth = 512;
    const int windowHeight = 380;


    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    const int gravity = 1;
    const int jumpVal = -22;

    const int width = 50;
    const int height = 80;

    int posY = windowHeight - height;
    int velosity = 0;

    SetTargetFPS(60);

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(WHITE);

        if(posY >= windowHeight - height){
            velosity = 0;
            if(IsKeyPressed(KEY_SPACE)){
                velosity += jumpVal;
            }
        }else {
            velosity += gravity;
        }

        posY += velosity;

        DrawRectangle(windowWidth / 2, posY, width, height, BLUE);

        EndDrawing();
    }
    CloseWindow();
}