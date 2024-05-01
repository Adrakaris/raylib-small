#include <raylib.h>
#include <iostream>
#include <cstdint>
#include <string>

#include "util.h"
// #include "board.h"
#include "gameScreen.h"

/*
Camera notes

camera seems to be pixel size at zoom 1
its target is the top left corner, so offset by minus half the screen wh will center it on 0,0
thisn seem to otherwise work the same though.
*/

const Color BG = colFromHex(0x2e2e2e);
const Color BGTrans = colFromHexAlpha(0x3e3e3ebb);
const Color button = colFromHexAlpha(0x5b5b61aa);
const Color button_active = colFromHex(0x5b5b61);
const Color green = colFromHex(0x00ff00);


class Game {

private:
    ScreenType screenType = GAME;
    GameScreen gameScreen { &screenType };
    // title screen goes here...

public:
    void update(float dt) {
        switch (screenType) {
            case TITLE:
                std::cout << "I detect I've been put into title screen mode. I don't have one of those." << std::endl;
            case GAME:
                gameScreen.update(dt);
        }
    }

    void draw() {
        switch (screenType) {
            case TITLE:
            case GAME:
                gameScreen.draw();
        }
    }

    // gamescreen should be automatically deconstructed

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

