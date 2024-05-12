#include "board.h"


Board::Board() {
    scaleShape(dashShape, 4, subBoardWidth);
    scaleShape(crossShapeAscend, 4, subBoardWidth);
    scaleShape(crossShapeDescend, 4, subBoardWidth);
}


// font struct is small anyway and its a shallow copy so should be fine
void Board::initialise(Font mainFont) {
    this->mainFont = mainFont;
}


void Board::reset() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            SubBoard* b = &(boards[i][j]);
            for (int ii = 0; ii < 3; ii++) {
                for (int jj = 0; jj < 3; jj++) {
                    b->values[ii][jj] = 0;
                }
            }
            b->isActive = false;
            b->isHovered = false;
            b->wonBy = 0;

        }
    }
    selecting = true;
}


void Board::updateHover(const Vector2& mousePos) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Rectangle boardbox = getRectOfSubboard(Index{i, j});
            if (CheckCollisionPointRec(mousePos, boardbox)) {
                boards[i][j].isHovered = true;
            } else {
                boards[i][j].isHovered = false;
            }
        }
    }
}

void Board::setActiveBoard(Index id) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            boards[i][j].isActive = false;
        }
    }

    if (boards[id.i][id.j].wonBy) {
        selecting = true;
    } else {
        boards[id.i][id.j].isActive = true;
    }
}

Index Board::getActiveBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (boards[i][j].isActive) return Index {i, j};
        }
    }
    return Index {-1, -1};
}

bool Board::setCell(Index onBoard, Index id, char player) {

    char* p_cell = &(boards[onBoard.i][onBoard.j].values[id.i][id.j]);
    if (*p_cell != 0) return false;
    *p_cell = player;
    return true;
}

bool Board::getHoveredBoard(const Vector2& mousePos, Index& out) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (boards[i][j].wonBy) continue;

            Rectangle box = getRectOfSubboard(Index{i, j});
            if (CheckCollisionPointRec(mousePos, box)) {
                out.i = i; out.j = j;
                return true;
            }
            
        }
    }
    return false;
}

bool Board::getHoveredCell(const Vector2& mousePos, const Index& parent, Index& out) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Rectangle box = getRectOfCell(parent, Index{i, j});
            if (CheckCollisionPointRec(mousePos, box)) {
                out.i = i; out.j = j;
                return true;
            }
            
        }
    }
    return false;
}


char Board::checkSubboardWon(Index id) {
    SubBoard* p_board = &boards[id.i][id.j];
    return checkSubboardWonHelper(*p_board);
}

char Board::checkSubboardWonHelper(SubBoard& board) {
    // wins
    for (int i = 0; i < 3; i++) {
        if (board.values[i][0] == board.values[i][1] && board.values[i][1] == board.values[i][2] && board.values[i][0] != 0) {
            // std::cout << "horizontal equal\n";
            return board.values[i][0];
        }
        if (board.values[0][i] == board.values[1][i] && board.values[1][i] == board.values[2][i] && board.values[0][i] != 0) {
            // std::cout << "vertical equal\n";
            return board.values[0][i];

        }
    }
    if (board.values[0][0] == board.values[1][1] && board.values[1][1] == board.values[2][2] && board.values[1][1] != 0) {
        return board.values[0][0];
    }
    if (board.values[0][2] == board.values[1][1] && board.values[1][1] == board.values[2][0] && board.values[1][1] != 0) {
        return board.values[0][2];
    }
    // draws
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board.values[i][j] == 0) {
                return 0;  // still empty, no draw
            }
        }
    }
    return 'd';  // draw
}


char Board::checkGameWon() {
    SubBoard temp;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp.values[i][j] = boards[i][j].wonBy;
        }
    }
    return checkSubboardWonHelper(temp);
}

void Board::markWonBy(Index id, char player) {
    boards[id.i][id.j].wonBy = player;
}



void Board::draw() {
    DrawRectangle(boardOffset.x - halfWidth, boardOffset.y - halfWidth, boardWidth, boardWidth, baseColor);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            drawSubBoard(Index{i, j});
        }
    }
}

void Board::drawSubBoard(Index id) {
    Rectangle rect = getRectOfSubboard(id);
    int i = id.i; int j = id.j;

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
    } else if (selecting) {
        DrawRectangleRounded(rect, 0.05, 8, subColor);
    }

    for (int ii = 0; ii < 3; ii++) {
        for (int jj = 0; jj < 3; jj++) {
            Rectangle cell = getRectOfCell(id, Index{ii, jj});
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
    DrawCircle(rect.x + subBoardWidth/2.0f, rect.y + subBoardWidth/2.0f, subBoardWidth*0.3, boardO);

}

void Board::drawWinningBoardD(Rectangle rect) {
    DrawRectangleRounded(rect, 0.05, 8, subColorActive);

    offsetShapeBy(dashShape, 4, Vector2{rect.x, rect.y});
    DrawTriangleStrip(dashShape, 4, cellBlank);
    offsetShapeBy(dashShape, 4, Vector2{-rect.x, -rect.y});
}

Rectangle Board::getRectOfSubboard(Index id) {
    int i = id.i; int j = id.j;
    float x = (boardGap-halfWidth+boardOffset.x) + i*(boardGap + subBoardWidth);
    float y = (boardGap-halfWidth+boardOffset.y) + j*(boardGap + subBoardWidth);
    return Rectangle {x, y, subBoardWidth, subBoardWidth};
}

Rectangle Board::getRectOfCell(Index parent, Index id) {
    Rectangle pRect = getRectOfSubboard(parent);

    float x = (pRect.x + cellGap) + id.i*(cellGap + cellWidth);
    float y = (pRect.y + cellGap) + id.j*(cellGap + cellWidth);
    return Rectangle {x, y, cellWidth, cellWidth};
}





// yes, this is ugly
// but it fun
std::ostream& operator << (std::ostream& stream, const Board& board) {
    char buffer[40] = { 0 };
    stream << "      == BOARD ==    \n";
    stream << "---------------------\n";  // 24 wide -- 5 inside
    for (int row = 0; row < 3; row++) {
        for (int subrow = 0; subrow < 3; subrow++) {
            sprintf(buffer, "|%c|%c|%c||%c|%c|%c||%c|%c|%c|\n",
                board.boards[row][0].values[subrow][0] == 0 ? ' ' : board.boards[row][0].values[subrow][0], 
                board.boards[row][0].values[subrow][1] == 0 ? ' ' : board.boards[row][0].values[subrow][1], 
                board.boards[row][0].values[subrow][2] == 0 ? ' ' : board.boards[row][0].values[subrow][2],
                board.boards[row][1].values[subrow][0] == 0 ? ' ' : board.boards[row][1].values[subrow][0], 
                board.boards[row][1].values[subrow][1] == 0 ? ' ' : board.boards[row][1].values[subrow][1], 
                board.boards[row][1].values[subrow][2] == 0 ? ' ' : board.boards[row][1].values[subrow][2],
                board.boards[row][2].values[subrow][0] == 0 ? ' ' : board.boards[row][2].values[subrow][0], 
                board.boards[row][2].values[subrow][1] == 0 ? ' ' : board.boards[row][2].values[subrow][1], 
                board.boards[row][2].values[subrow][2] == 0 ? ' ' : board.boards[row][2].values[subrow][2]
            );
            stream << buffer;               
            
        }
        sprintf(buffer, "|Hov %d||Hov %d||Hov %d|\n", board.boards[row][0].isHovered, board.boards[row][1].isHovered, board.boards[row][2].isHovered);
        stream << buffer;
        sprintf(buffer, "|Act %d||Act %d||Act %d|\n", board.boards[row][0].isActive, board.boards[row][1].isActive, board.boards[row][2].isActive);
        stream << buffer;
        sprintf(buffer, "|Won %c||Won %c||Won %c|\n", 
            board.boards[row][0].wonBy == 0 ? '_' : board.boards[row][0].wonBy, 
            board.boards[row][1].wonBy == 0 ? '_' : board.boards[row][1].wonBy, 
            board.boards[row][2].wonBy == 0 ? '_' : board.boards[row][2].wonBy
        );
        stream << buffer;
        stream << "---------------------\n"; 
    }

    return stream;

}


void offsetShapeBy(Vector2* points, int num, Vector2 offset) {
    for (int i = 0; i < num; i++) {
        points[i] = Vector2Add(points[i], offset);
    }
}

