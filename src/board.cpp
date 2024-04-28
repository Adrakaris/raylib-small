#include "board.h"



Board::Board(int boardWidth, float subBoardWidth, Vector2 boardOffset) {
    this->boardWidth = boardWidth;
    this->subBoardWidth = subBoardWidth;
    this->boardGap = (float)(boardWidth - 3*subBoardWidth) / 4.0f;
    this->boardOffset = boardOffset;
    this->halfWidth = boardWidth / 2.0f;
}


void Board::reset() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; i < 3; i++) {
            boards[i][j] = SubBoard();
        }
    }
}


void Board::draw() {
    DrawRectangle(boardOffset.x - halfWidth, boardOffset.y - halfWidth, boardWidth, boardWidth, baseColor);

    // std::cout<<"new frame\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            drawSubBoard(i, j);
        }
    }
}


void Board::drawSubBoard(int i, int j) {
    Rectangle rect = getRectOfSubboard(i, j);
    if (boards[i][j].isHovered) {
        DrawRectangleRounded(rect, 0.05, 8, subColorHovered);
    } else {
        DrawRectangleRounded(rect, 0.05, 8, subColor);
    }
}


Rectangle Board::getRectOfSubboard(int i, int j) {
    float x = (boardGap-halfWidth+boardOffset.x) + i*(boardGap + subBoardWidth);
    float y = (boardGap-halfWidth+boardOffset.y) + j*(boardGap + subBoardWidth);
    return Rectangle {x, y, subBoardWidth, subBoardWidth};
}


void Board::update(Vector2& mousePos) {
    updateMouseInput(mousePos);
}


void Board::updateMouseInput(Vector2& mousePos) {
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Rectangle boardbox = getRectOfSubboard(i, j);
            if (CheckCollisionPointRec(mousePos, boardbox)) {
                boards[i][j].isHovered = true;
            } else {
                boards[i][j].isHovered = false;
            }
        }
    }
}


std::ostream& operator << (std::ostream& stream, const Board& board) {
    char outString[128];
    sprintf(outString, "Board(width=%d, subwidth=%f, gap=%.2f)", board.boardWidth, board.subBoardWidth, board.boardGap);
    return (stream << outString); 
}

// std::ostream& operator << (std::ostream stream, const SubBoard& subBoard) {
    
// }
