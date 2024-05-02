#pragma once 

#include <raylib.h>
#include <iostream>
#include "util.h"
#include "components.h"



class TitleScreen : Screen {

private:
    const float cameraScale = SCALE / (float)GetScreenHeight();
    Camera2D mainCamera {
         {0.0f, 0.0f}, {-cameraScale*GetScreenWidth()/2.0f, -cameraScale*GetScreenHeight()/2.0f}, 0.0f, 1.0f/cameraScale
    };
    Font font;

    RectButton playButton {MOUSE_BUTTON_LEFT, Rectangle{-80, -90, 160, 40}, button, button_active, button_down};

public:
    TitleScreen(ScreenType* screenRef);
    void update(float dt) override;
    void draw() override;
    void initialise(Font& font);
    ~TitleScreen(); 

};

