#include "board.h"



Board::Board() {
    this->boardGap = (float)(boardWidth - 3*subBoardWidth) / 4.0f;
    this->halfWidth = boardWidth / 2.0f;
    this->cellWidth = (subBoardWidth - 3*cellWidth) / 4.0f;
    
    scaleShape(dashShape, 4, subBoardWidth);
    scaleShape(crossShapeAscend, 4, subBoardWidth);
    scaleShape(crossShapeDescend, 4, subBoardWidth);
}

void Board::setFont(Font& mainFont) {
    this->mainFont = mainFont;
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

    drawInformation();
}


void Board::drawInformation() {
    // set corner to right side
    Vector2 topLeft {
        boardOffset.x + halfWidth + boardGap,
        boardOffset.y - halfWidth
    };

    // current turn:
    DrawTextEx(mainFont, "Turn", topLeft, 16, 0, textColorDark);

    Color col;
    switch (currentTurn) {
        case 'x': col = cellX; break;
        case 'o': col = cellO; break;
        default: col = cellBlank;
    }
    topLeft.y += 18;
    DrawRectangleRounded(Rectangle{topLeft.x+4, topLeft.y, cellWidth, cellWidth}, 0.15, 6, col);

}


void Board::drawSubBoard(int i, int j) {
    Rectangle rect = getRectOfSubboard(i, j);

    if (boards[i][j].wonBy == 'x') {
        drawWinningBoardX(rect);
    } else if (boards[i][j].wonBy == 'o') {
        drawWinningBoardO(rect);
    } else if (boards[i][j].wonBy == 'd') {
        drawWinningBoardD(rect);
    } else if (boards[i][j].isActive) {
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

void Board::scaleShape(Vector2* points, int numPoints, float scale) {
    for (int i = 0; i < numPoints; i++) {
        std::cout << "Prev shape " << points[i].x << "," << points[i].y << "; ";
        points[i] = Vector2Scale(points[i], scale);
        std::cout << "New shape " << points[i].x << "," << points[i].y << "; " << std::endl;
    }
}

void offsetShapeBy(Vector2* points, int num, Vector2 offset) {
    for (int i = 0; i < num; i++) {
        points[i] = Vector2Add(points[i], offset);
    }
}

void Board::drawWinningBoardX(Rectangle rect) {
    DrawRectangleRounded(rect, 0.05, 8, boardX);

    offsetShapeBy(crossShapeAscend, 4, Vector2{rect.x, rect.y});
    offsetShapeBy(crossShapeDescend, 4, Vector2{rect.x, rect.y});
    DrawTriangleStrip(crossShapeAscend, 4, boardXSaturate);
    DrawTriangleStrip(crossShapeDescend, 4, boardXSaturate);
    offsetShapeBy(crossShapeAscend, 4, Vector2{-rect.x, -rect.y});
    offsetShapeBy(crossShapeDescend, 4, Vector2{-rect.x, -rect.y});
}

void Board::drawWinningBoardO(Rectangle rect) {
    DrawRectangleRounded(rect, 0.05, 8, boardO);

    DrawCircle(rect.x + subBoardWidth/2.0f, rect.y + subBoardWidth/2.0f, subBoardWidth*0.45, boardOSaturate);
    DrawCircle(rect.x + subBoardWidth/2.0f, rect.y + subBoardWidth/2.0f, subBoardWidth*0.35, boardO);

}

void Board::drawWinningBoardD(Rectangle rect) {
    DrawRectangleRounded(rect, 0.05, 8, subColorActive);

    offsetShapeBy(dashShape, 4, Vector2{rect.x, rect.y});
    DrawTriangleStrip(dashShape, 4, cellBlank);
    offsetShapeBy(dashShape, 4, Vector2{-rect.x, -rect.y});
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
        return;
    }

    // use the play
    Index activeBoard = getActiveBoard();
    activateCell(mousePos, activeBoard.i, activeBoard.j);
}

bool Board::selectBoard(Vector2& mousePos) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (boards[i][j].wonBy) continue;

            Rectangle box = getRectOfSubboard(i, j);

            if (CheckCollisionPointRec(mousePos, box)) {
                boards[i][j].isActive = true;
                return true;
            }
            
        }
    }
    return false;
}

bool Board::activateCell(Vector2& mousePos, int i, int j) {
    for (int ii = 0; ii < 3; ii++) {
        for (int jj = 0; jj < 3; jj++) {

            Rectangle box = getRectOfCell(i, j, ii, jj);

            if (CheckCollisionPointRec(mousePos, box)) {
                // dbg_cycleCell(i, j, ii, jj);
                char* p_cell = &(boards[i][j].values[ii][jj]);
                if (*p_cell != 0) return false;
                // switch cells 
                *p_cell = currentTurn;
                if (currentTurn == 'x') {
                    currentTurn = 'o';
                } else {
                    currentTurn = 'x';
                }
                return true;
            }
        }
    }
    return false;
}

Index Board::getActiveBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (boards[i][j].isActive) return Index {i, j};
        }
    }
    return Index {-1, -1};
}

void Board::dbg_cycleCell(int boardi, int boardj, int celli, int cellj) {
    char* p_cell = &(boards[boardi][boardj].values[celli][cellj]);
    if (*p_cell == 0) {
        *p_cell = 'x';
    } else if (*p_cell == 'x') {
        *p_cell = 'o';
    } else {
        *p_cell = 0;
    }
}

std::ostream& operator << (std::ostream& stream, const Board& board) {
    char outString[128];
    sprintf(outString, "Board(width=%d, subwidth=%f, gap=%.2f)", board.boardWidth, board.subBoardWidth, board.boardGap);
    return (stream << outString); 
}

// std::ostream& operator << (std::ostream stream, const SubBoard& subBoard) {
    
// }
