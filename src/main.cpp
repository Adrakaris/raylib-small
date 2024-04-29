#include <raylib.h>
#include <iostream>
#include <cstdint>

#include "util.h"
#include "board.h"

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
    const float cameraScale = SCALE/GetScreenHeight();

    Camera2D mainCamera {
        // {0.0f, 0.0f}, {-GetScreenWidth()/2.0f, -GetScreenHeight()/2.0f}, 0.0f, 1.0f/cameraScale
         {0.0f, 0.0f}, {-cameraScale*GetScreenWidth()/2.0f, -cameraScale*GetScreenHeight()/2.0f}, 0.0f, 1.0f/cameraScale
    };  // target, offset, rotation, scale

    Font font;
    
    Board board;

public:

    Game() {
        font = LoadFontEx("assets/font/lora_var.TTF", 96, 0, 0);
        GenTextureMipmaps(&font.texture);

        board.setFont(font);

        std::cout << board << std::endl;
    }

    void update(float dt) {
        Vector2 screenMousePos = GetMousePosition();
        Vector2 realMousePos = GetScreenToWorld2D(screenMousePos, mainCamera);

        board.update(realMousePos);
    }

    void draw() {
        BeginDrawing();
        ClearBackground(BG);
        // the fact that the camera automatically starts using screen coords when this is called is kinda goated
        drawMainCamera();

        EndDrawing();
    }

    ~Game() {
        UnloadFont(font);
    }

private:
    // call ONLY in the draw function, since this assumes you've begun drawing
    void drawMainCamera() {
        BeginMode2D(mainCamera);

        // draw title and stuff
        DrawTextEx(font, "Tic Tac Toe (Big)", Vector2{-120, -145}, 30, 0, textColorDark);

        board.draw();

        EndMode2D();
    }

};


int main() {

    std::cout << __cplusplus << std::endl;

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

