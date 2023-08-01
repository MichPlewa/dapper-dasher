#include <raylib.h>

int main(){
    const int width = 512;
    const int height = 380;

    SetTargetFPS(60);

    InitWindow(width, height, "Dasher");

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }
}