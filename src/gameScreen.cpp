#include "gameScreen.h"



GameScreen::GameScreen(ScreenType* screenRef) : Screen(screenRef) {

}


void GameScreen::initialise(Font& font) {
    this->font = font;
    board.setFont(font);
}


void GameScreen::update(float dt) {
    Vector2 screenMousePos = GetMousePosition();
    Vector2 realMousePos = GetScreenToWorld2D(screenMousePos, mainCamera);

    if (!board.isGameWon) {
        board.update(realMousePos);
    } else {
        if (CheckCollisionPointRec(realMousePos, restartButton)) {
            buttonHovered = true;
        } else {
            buttonHovered = false;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && buttonHovered) {
            board.reset();
        }
    }

    // secret force exit control
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_B)) {
        *screenRef = TITLE;
    }
}


void GameScreen::draw() {
    BeginDrawing();
    ClearBackground(BG);
    // the fact that the camera automatically starts using screen coords when this is called is kinda goated
    drawMainCamera();

    EndDrawing();
}


void GameScreen::drawMainCamera() {
    BeginMode2D(mainCamera);

    // draw title and stuff
    DrawTextEx(font, "Tic Tac Toe (Big)", Vector2{-120, -145}, 30, 0, textColorDark);
    // DrawCentredText(font, "Tic Tac Toe (Big)", Vector2{0, -145}, 30, 0, textColorDark);

    board.draw();

    if (board.isGameWon) {
        DrawRectangleRounded(Rectangle{-180, -100, 360, 200}, 0.01, 8, BGTrans);
        
        if (board.isGameWon != 'd') {
            DrawCentredText(font, "Winner Winner!", Vector2{0, -85}, 40, 0, textColorDark);
            const char* whoWon = TextFormat("%c has won the game!", std::toupper(board.isGameWon));
            DrawCentredText(font, whoWon, Vector2{0, -40}, 28, 0, board.isGameWon == 'x' ? board.cellX : board.cellO);
        } else {
            DrawCentredText(font, "Woah!", Vector2{0, -85}, 40, 0, textColorDark);
            DrawCentredText(font, "It is a draw!", Vector2{0, -40}, 28, 0, textColorDark);
        }

        if (buttonHovered) {
            DrawRectangleRounded(restartButton, 0.05, 8, button_active);
        } else {
            DrawRectangleRounded(restartButton, 0.05, 8, button);
        }
        const char* restart = "Restart";
        Vector2 restartDim = MeasureTextEx(font, restart, 40, 0);
        DrawTextEx(font, restart, Vector2{-restartDim.x/2.0f, 30}, 40, 0, textColorDark);

    }

    EndMode2D();
}



GameScreen::~GameScreen() {
}
