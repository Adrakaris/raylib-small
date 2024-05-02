#include "titleScreen.h"


TitleScreen::TitleScreen(ScreenType* screenRef) : Screen(screenRef) {}


void TitleScreen::initialise(Font& font) {
    this->font = font;
}


void TitleScreen::update(float dt) {
    Vector2 screenMousePos = GetMousePosition();
    Vector2 realMousePos = GetScreenToWorld2D(screenMousePos, mainCamera);

    playButton.update(realMousePos);
    if (playButton.getState()) {
        std::cout << "Button is pressed!" << std::endl;
    }

    // secret force exit control
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_B)) {
        *screenRef = GAME;
    }
}

void TitleScreen::draw() {
    BeginDrawing();
    ClearBackground(BG);
    BeginMode2D(mainCamera);
    // blah blah blah
    DrawCentredText(font, "Tic Tac Toe (Big)", Vector2{0, -145}, 30, 0, textColorDark);
    // DrawCentredText(font, "This title screen is under construction", Vector2{0, -115}, 16, 0, textColorDark);
    playButton.draw();


    EndMode2D();
    EndDrawing();
}

TitleScreen::~TitleScreen() {}


void toMainGameCallback() {
    
}

