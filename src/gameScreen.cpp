#include "gameScreen.h"


const Color BG = colFromHex(0x2e2e2e);
const Color BGTrans = colFromHexAlpha(0x3e3e3ebb);
const Color button = colFromHexAlpha(0x5b5b61aa);
const Color button_active = colFromHex(0x5b5b61);
const Color green = colFromHex(0x00ff00);


GameScreen::GameScreen(ScreenType* screenRef) : Screen(screenRef) {
    font = LoadFontEx("assets/font/lora_var.TTF", 128, 0, 0);
    GenTextureMipmaps(&font.texture);

    board.setFont(font);
    // std::cout << board << std::endl;
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
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_B)) {
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

    board.draw();

    if (board.isGameWon) {
        DrawRectangleRounded(Rectangle{-180, -100, 360, 200}, 0.01, 8, BGTrans);
        
        if (board.isGameWon != 'd') {
            const char* winText = "Winner Winner!";
            Vector2 winTextDim = MeasureTextEx(font, winText, 40, 0);
            DrawTextEx(font, winText, Vector2{-winTextDim.x/2.0f, -85}, 40, 0, textColorDark);
            const char* whoWon = TextFormat("%c has won the game!", std::toupper(board.isGameWon));
            Vector2 whoWonDim = MeasureTextEx(font, whoWon, 28, 0);
            DrawTextEx(font, whoWon, Vector2{-whoWonDim.x/2.0f, -40}, 28, 0, board.isGameWon == 'x' ? board.cellX : board.cellO);
        } else {
            const char* winText = "Woah!";
            Vector2 winTextDim = MeasureTextEx(font, winText, 40, 0);
            DrawTextEx(font, winText, Vector2{-winTextDim.x/2.0f, -85}, 40, 0, textColorDark);
            const char* whoWon = "It is a draw!";
            Vector2 whoWonDim = MeasureTextEx(font, whoWon, 28, 0);
            DrawTextEx(font, whoWon, Vector2{-whoWonDim.x/2.0f, -40}, 28, 0, textColorDark);
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
    UnloadFont(font);
}
