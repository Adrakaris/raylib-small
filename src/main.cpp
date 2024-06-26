#include <raylib.h>
#include <iostream>
#include <cstdint>
#include <string>

#include "util.h"
// #include "board.h"
#include "titleScreen.h"
#include "standardScreen.h"

/*
Camera notes

camera seems to be pixel size at zoom 1
its target is the top left corner, so offset by minus half the screen wh will center it on 0,0
thisn seem to otherwise work the same though.
*/


class Game {
private:

    Font mainFont;
    ScreenType screenType = TITLE;

    StandardScreen standardGameScreen { &screenType };
    TitleScreen titleScreen { &screenType };

public:
    Game() {
        mainFont = LoadFontEx("assets/font/lora_var.TTF", 128, 0, 0);
        GenTextureMipmaps(&mainFont.texture);
        standardGameScreen.initialise(mainFont);
        titleScreen.initialise(mainFont);
    }

    void update(float dt) {
        switch (screenType) {
            case TITLE:
                // std::cout << "I detect I've been put into title screen mode. I don't have one of those." << std::endl;
                titleScreen.update(dt); break;
            case GAME:
                standardGameScreen.update(dt);
        }
    }

    void draw() {
        switch (screenType) {
            case TITLE:
                titleScreen.draw(); break;
            case GAME:
                standardGameScreen.draw();
        }
    }

    // gamescreen should be automatically deconstructed
    ~Game() {
        UnloadFont(mainFont);
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

