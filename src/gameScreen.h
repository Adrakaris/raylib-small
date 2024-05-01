#pragma once 

#include <raylib.h>
#include "util.h"
#include "board.h"


class GameScreen : Screen {
private:
    const float cameraScale = SCALE / (float)GetScreenHeight();
    Camera2D mainCamera {
         {0.0f, 0.0f}, {-cameraScale*GetScreenWidth()/2.0f, -cameraScale*GetScreenHeight()/2.0f}, 0.0f, 1.0f/cameraScale
    };
    Font font;
    Board board;
    const Rectangle restartButton {-80,20,160,60};
    bool buttonHovered = false;

public:
    GameScreen(ScreenType* screenRef);
    void update(float dt) override;
    void draw() override;
    void initialise(Font& font);
    ~GameScreen();

private:
    void drawMainCamera();

};



