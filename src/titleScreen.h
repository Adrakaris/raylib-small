#pragma once 

#include <raylib.h>
#include "util.h"


// const Color BG = colFromHex(0x2e2e2e);
// const Color BGTrans = colFromHexAlpha(0x3e3e3ebb);
// const Color button = colFromHexAlpha(0x5b5b61aa);
// const Color button_active = colFromHex(0x5b5b61);
// const Color green = colFromHex(0x00ff00);


class TitleScreen : Screen {

private:
    const float cameraScale = SCALE / (float)GetScreenHeight();
    Camera2D mainCamera {
         {0.0f, 0.0f}, {-cameraScale*GetScreenWidth()/2.0f, -cameraScale*GetScreenHeight()/2.0f}, 0.0f, 1.0f/cameraScale
    };
    Font font;

public:
    TitleScreen(ScreenType* screenRef);
    void update(float dt) override;
    void draw() override;
    void initialise(Font& font);
    ~TitleScreen(); 

};

