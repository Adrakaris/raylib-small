#include "standardScreen.h"


void StandardScreen::initialise(Font font) {
    this->font = font;
    board.initialise(font);
}


void StandardScreen::update(float dt) {
    Vector2 screenMousePos = GetMousePosition();
    Vector2 realMousePos = GetScreenToWorld2D(screenMousePos, mainCamera);

    if (!winner) {
        board.updateHover(realMousePos);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            handleMouseClick(realMousePos);
        }

        // secret testing function
        if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON)) {
            board.setSelecting();
        }

        playingQuitButton.update(realMousePos);
        if (playingQuitButton.getState()) {
            resetThisGame();
            *screenRef = TITLE;
        }
    } else {
        restartButton.update(realMousePos);
        if (restartButton.getState()) { resetThisGame(); }

        quitButton.update(realMousePos);
        if (quitButton.getState()) { 
            resetThisGame(); 
            *screenRef = TITLE; 
        }
    }

    // secret force exit control
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_B)) {
        *screenRef = TITLE;
    }
}

void StandardScreen::resetThisGame() {
    board.reset();
    winner = 0;
    turn = 'x';
}

void StandardScreen::handleMouseClick(Vector2& mousePos) {
    // multiple things with mouse click:
    // if is selecting, then use mouse to select a smaller board
    // otherwise, use mouse to play a piece on the board

    Index idx; // this index is used for return values 

    if (board.isSelecting()) {
        bool success = board.getHoveredBoard(mousePos, idx);
        if (!success) return;
        board.setActiveBoard(idx);
        board.unsetSelecting();
        return;
    }

    // playing within a board 
    Index active = board.getActiveBoard();
    // this tries to make sure we play properly
    if (!board.getHoveredCell(mousePos, active, idx)) return;
    if (!board.setCell(active, idx, turn)) return;

    if (char won = board.checkSubboardWon(active)) {
        std::cout << "Sub board won by: " << won << "\n";
        std::cout << board << std::endl;
        winner = board.checkGameWon();
    }

    if (turn == 'x') {
        turn = 'o';
    } else {
        turn = 'x';
    }

    board.setActiveBoard(idx); 

}


void StandardScreen::draw() {
    BeginDrawing();
    ClearBackground(BG);
    drawMainCamera();
    EndDrawing();
}

void StandardScreen::drawMainCamera() {
    BeginMode2D(mainCamera);

    // draw title and stuff
    DrawTextEx(font, "Tic Tac Toe | 2P", Vector2{-120, -145}, 30, 0, textColorDark);

    board.draw();
    drawTurnInformation();

    if (winner) {
        DrawRectangleRounded(Rectangle{-180, -100, 360, 200}, 0.01, 8, BGTrans);
        
        if (winner != DRAW) {
            DrawCentredText(font, "Winner Winner!", Vector2{0, -85}, 40, 0, textColorDark);
            const char* whoWon = TextFormat("%c has won the game!", std::toupper(winner));
            DrawCentredText(font, whoWon, Vector2{0, -40}, 28, 0, winner == X ? board.cellX : board.cellO);
        } else {
            DrawCentredText(font, "Woah!", Vector2{0, -85}, 40, 0, textColorDark);
            DrawCentredText(font, "It is a draw!", Vector2{0, -40}, 28, 0, textColorDark);
        }

        restartButton.draw();
        DrawCentredText(font, "Restart", Vector2{0, 7}, 26, 0, textColorDark);
        quitButton.draw();
        DrawCentredText(font, "Back to Menu", Vector2{0, 52}, 26, 0, textColorDark);
    } else {
        playingQuitButton.draw();
        DrawCentredText(font, "Quit", Vector2{playingQuitButton.rect.x + playingQuitButton.rect.width/2.0f, playingQuitButton.rect.y+4}, 12, 0, textColorDark);
    }


    EndMode2D();
}

void StandardScreen::drawTurnInformation() {
    DrawTextEx(font, "Turn", board.leftsideTop, 16, 0, textColorDark);

    Color col;
    switch (turn) {
        case X: col = board.cellX; break;
        case O: col = board.cellO; break;
        default: col = board.cellBlank;
    }
    DrawRectangleRounded(Rectangle{board.leftsideTop.x+4, board.leftsideTop.y + 18, board.cellWidth, board.cellWidth}, 0.15, 6, col);
}

