#include <raylib.h>
#include <iostream>
#include <cstdint>

#include "defs.h"

/*
Camera notes

camera seems to be pixel size at zoom 1
its target is the top left corner, so offset by minus half the screen wh will center it on 0,0
thisn seem to otherwise work the same though.
*/

const Color BG = colFromHex(0x2e2e2e);
const Color green = colFromHex(0x00ff00);


class Game {
private:
    float cameraScale = SCALE/GetScreenHeight();
    Camera2D mainCamera {
        // {0.0f, 0.0f}, {-GetScreenWidth()/2.0f, -GetScreenHeight()/2.0f}, 0.0f, 1.0f/cameraScale
        {0.0f, 0.0f}, {-cameraScale*GetScreenWidth()/2.0f, -cameraScale*GetScreenHeight()/2.0f}, 0.0f, 1.0f/cameraScale
    };  // target, offset, rotation, scale


    

public:

    Game() {

    }

    void update(float dt) {

    }

    void draw() {
        BeginDrawing();
        ClearBackground(BG);
        // the fact that the camera automatically starts using screen coords when this is called is kinda goated
        drawMainCamera();

        EndDrawing();
    }

    ~Game() {

    }

private:
    // call ONLY in the draw function, since this assumes you've begun drawing
    void drawMainCamera() {
        BeginMode2D(mainCamera);

        unsigned int colHex = 0x333333;

        for (int i = 50; i >= 0; i-=5) {
            Color boxCol = colFromHex(colHex);
            // DrawRectangle(-i, -i, 2*i, 2*i, boxCol);
            DrawCircle(0, 0, i, boxCol);
            colHex += 0x220066;
        }

        for (int i = -160; i <= 160; i+=40) {
            DrawLine(-1, i, 1, i, green);
            // DrawRectangle(-5, i-1, 10, 2, green);
            DrawText(TextFormat("%d", i), 2, i-1, 1, green);
        }
        for (int i = -320; i <= 320; i+=40) {
            DrawLine(i, -1, i, 1, green);
            DrawText(TextFormat("%d", i), i, 4, 1, green);
        }

        EndMode2D();
    }

};


int main() {

    // InitWindow(720, 480, "Tic Tac Toe Game");
    InitWindow(1440, 960, "Tic Tac Toe Game");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {

        game.update(GetFrameTime());

        game.draw();

    }

    return 0;
}

