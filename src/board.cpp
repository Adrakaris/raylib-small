#include "board.h"



Board::Board() {
    this->boardGap = (float)(boardWidth - 3*subBoardWidth) / 4.0f;
    this->halfWidth = boardWidth / 2.0f;
    this->cellWidth = (subBoardWidth - 3*cellWidth) / 4.0f;
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

    if (boards[i][j].isActive) {
        DrawRectangleRounded(rect, 0.05, 8, subColorActive);
    } else if (boards[i][j].isHovered) {
        DrawRectangleRounded(rect, 0.05, 8, subColorHovered);
    } else {
        DrawRectangleRounded(rect, 0.05, 8, subColor);
    }

    for (int ii = 0; ii < 3; ii++) {
        for (int jj = 0; jj < 3; jj++) {
            Rectangle cell = getRectOfCell(i, j, ii, jj);
            Color toColor;
            switch (boards[i][j].values[ii][jj]) {
                case 0: toColor = cellBlank; break;
                case 'x': toColor = cellX; break;
                case 'o': toColor = cellO; break;
                default: toColor = cellBlank;
            }
            // std::cout << "[" << cell.x << " " << cell.y << " " << cell.width << " " << cell.height << " " << std::endl;
            DrawRectangleRounded(cell, 0.15, 6, toColor);
        }
    }
}


Rectangle Board::getRectOfSubboard(int i, int j) {
    float x = (boardGap-halfWidth+boardOffset.x) + i*(boardGap + subBoardWidth);
    float y = (boardGap-halfWidth+boardOffset.y) + j*(boardGap + subBoardWidth);
    return Rectangle {x, y, subBoardWidth, subBoardWidth};
}


Rectangle Board::getRectOfCell(int parent_i, int parent_j, int i, int j) {
    Rectangle parent = getRectOfSubboard(parent_i, parent_j);

    float x = (parent.x + cellGap) + i*(cellGap + cellWidth);
    float y = (parent.y + cellGap) + j*(cellGap + cellWidth);
    return Rectangle {x, y, cellWidth, cellWidth};
}


void Board::update(Vector2& mousePos) {
    updateMouseInput(mousePos);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        handleMouseClick(mousePos);
    }

    // secret testing function
    if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON)) {
        makeSelecting();
    }
}

void Board::makeSelecting() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            boards[i][j].isActive = false;
        }
    }
    isSelecting = true;
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

void Board::handleMouseClick(Vector2& mousePos) {  
    // multiple things with mouse click:
    // if is selecting, then use mouse to select a smaller board
    // otherwise, use mouse to play a piece on the board

    if (isSelecting) {
        bool success = selectBoard(mousePos);
        if (success) isSelecting = false;
    }

}

bool Board::selectBoard(Vector2& mousePos) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (boards[i][j].isWon) continue;

            Rectangle box = getRectOfSubboard(i, j);

            if (CheckCollisionPointRec(mousePos, box)) {
                boards[i][j].isActive = true;
                return true;
            }
            
        }
    }
    return false;
}

std::ostream& operator << (std::ostream& stream, const Board& board) {
    char outString[128];
    sprintf(outString, "Board(width=%d, subwidth=%f, gap=%.2f)", board.boardWidth, board.subBoardWidth, board.boardGap);
    return (stream << outString); 
}

// std::ostream& operator << (std::ostream stream, const SubBoard& subBoard) {
    
// }
