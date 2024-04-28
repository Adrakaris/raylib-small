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


class Game {
private:
    float cameraScale = SCALE/GetScreenHeight();
    Camera2D camera {
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
        BeginMode2D(camera);
            unsigned int colHex = 0x333333ff;

            for (int i = 50; i >= 0; i-=5) {
                Color boxCol = colourFromHex(colHex);
                // DrawRectangle(-i, -i, 2*i, 2*i, boxCol);
                DrawCircle(0, 0, i, boxCol);
                colHex += 0x22006600;
                std::cout << std::hex << colHex << " ";
            }
            std::cout << std::endl;

            // for (int i = )

            
        EndMode2D();
        EndDrawing();
    }

    ~Game() {

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

