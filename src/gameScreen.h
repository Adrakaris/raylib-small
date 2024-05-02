#pragma once 

#include <raylib.h>
#include "util.h"
#include "board.h"
#include "components.h"


class GameScreen : Screen {
private:
    const float cameraScale = SCALE / (float)GetScreenHeight();
    Camera2D mainCamera {
         {0.0f, 0.0f}, {-cameraScale*GetScreenWidth()/2.0f, -cameraScale*GetScreenHeight()/2.0f}, 0.0f, 1.0f/cameraScale
    };
    Font font;
    Board board;
    RectButton restartButton { MOUSE_BUTTON_LEFT, Rectangle {-80,0,160,40}, button, button_active, button_down, 0.05, 8 };
    RectButton quitButton { MOUSE_BUTTON_LEFT, Rectangle {-80, 45, 160, 40}, button, button_active, button_down, 0.05, 8};
    RectButton playingQuitButton { MOUSE_BUTTON_LEFT, Rectangle {board.getBottomLeftOfBoard().x, board.getBottomLeftOfBoard().y-20, 32, 20},
                                   button, button_active, button_down, 0.1, 8};

public:
    GameScreen(ScreenType* screenRef);
    void update(float dt) override;
    void draw() override;
    void initialise(Font& font);
    ~GameScreen();

private:
    void drawMainCamera();

};



