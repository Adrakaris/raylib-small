#pragma once 

#include <raylib.h>
#include <iostream>
#include <format>
#include <raymath.h>
#include <memory>

#include "util.h"


constexpr char X = 'x';
constexpr char O = 'o';
constexpr char DRAW = 'd';
constexpr char ZERO = 0;

struct Index {
    int i, j;
};

// 'x' and 'o' for players, 'd' for draw and 0 for empty
struct SubBoard {
    char values[3][3] = {0};
    bool isHovered = false;
    bool isActive = false;
    char wonBy = 0;
};


void offsetShapeBy(Vector2* points, int num, Vector2 offset);
void printBoard(SubBoard& board);


/// @brief Board class -- handles drawing, display, and setting of board. Does not handle logic.
class Board {
public:
    const Color cellX = colFromHex(0xc96767);
    const Color cellO = colFromHex(0x6d84c9);
    const Color cellBlank = colFromHexAlpha(0x5b5b61aa);
    const Color baseColor = colFromHex(0x3e3e3e);
    const Color subColor = colFromHex(0x323236);
    const Color subColorActive = colFromHex(0x4b4b50);
    const Color subColorHovered = colFromHex(0x36363a);

    const Color boardX = colFromHex(0xa87676);
    const Color boardXSaturate = colFromHex(0xd13636);
    const Color boardO = colFromHex(0x697494);
    const Color boardOSaturate = colFromHex(0x2a53c9);

    // predefined
    const float boardWidth = 260;
    const float subBoardWidth = 80;
    const Vector2 boardOffset {0, 20};
    const float cellGap = 5;
    // calculated
    const float halfWidth = boardWidth / 2.0f;
    const float boardGap = (boardWidth - 3*subBoardWidth) / 4.0f;
    const float cellWidth = (subBoardWidth - 4*cellGap) / 3.0f;
    const Vector2 leftsideTop {boardOffset.x + halfWidth + boardGap, boardOffset.y - halfWidth};
    const Vector2 leftsideBottom {boardOffset.x + halfWidth + boardGap, boardOffset.y + halfWidth};
    
private:
    // cached shapes 
    Vector2 dashShape[4] = {
        {0, 0.2}, {0, 0.4}, {1, 0.6}, {1, 0.8}
    };
    Vector2 crossShapeAscend[4] {
        {0.05, 1-0.1914}, {0.1914, 1-0.05}, {1-0.1914, 0.05}, {1-0.05, 0.1914}
    };
    Vector2 crossShapeDescend[4] {
        {0.05, 0.1914}, {1-0.1914, 1-0.05}, {0.1914, 0.05}, {1-0.05, 1-0.1914}
    };

    Font mainFont;
    SubBoard boards[3][3] {};
    bool selecting = true;
    // char isGameWon = 0;

public:
    Board();
    void initialise(Font mainFont);
    void reset();
    void draw();
    // strictly update the state of the hover only
    void updateHover(const Vector2& mousePos);

    // set active board and deactivate all other boards -- will set selecting to true if given index is occupied
    void setActiveBoard(Index id);
    Index getActiveBoard();
    // set active cell -- will return false if the active cell is occupied and do nothing
    bool setCell(Index onBoard, Index id, char player);
    void setSelecting() { selecting = true; }
    void unsetSelecting() { selecting = false; }
    bool isSelecting() { return selecting; }

    // returns true if the mouse is over a selectable board; actual index is stored in out param
    bool getHoveredBoard(const Vector2& mousePos, Index& out);
    // returns true if the mouse is over a valid cell; actual index is stored in out param
    bool getHoveredCell(const Vector2& mousePos, const Index& parent, Index& out);

    // checks if a smaller board is won, update internally accordingly, returns 'x' 'o' 'd' or (0)
    char checkSubboardWon(Index id);
    // checks if the game is won, returns 'x', 'o', 'd' or  (0)
    char checkGameWon();
    // marks a subboard as won by a player 'x', 'o', 'd'
    void markWonBy(Index id, char player);

private:
    void drawSubBoard(Index id);
    void drawWinningBoardX(Rectangle rect);
    void drawWinningBoardO(Rectangle rect);
    void drawWinningBoardD(Rectangle rect);

    // get bounding box of sub-board
    Rectangle getRectOfSubboard(Index id);  
    Rectangle getRectOfCell(Index parent, Index id);
    // used in checking subboard won and game won
    char checkSubboardWonHelper(SubBoard& board); 
    
    friend std::ostream& operator <<(std::ostream& stream, const Board& board);
};





