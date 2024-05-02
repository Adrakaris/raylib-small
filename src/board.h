#pragma once 

#include <raylib.h>
#include <iostream>
#include <format>
#include <raymath.h>

#include "util.h"


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

class Board {
public:
    char isGameWon = 0;

    const Color cellX = colFromHex(0xc96767);
    const Color cellO = colFromHex(0x6d84c9);
    const Color cellBlank = colFromHexAlpha(0x5b5b61aa);

private:
    const Color baseColor = colFromHex(0x3e3e3e);
    const Color subColor = colFromHex(0x323236);
    const Color subColorActive = colFromHex(0x4b4b50);
    const Color subColorHovered = colFromHex(0x36363a);

    const Color boardX = colFromHex(0xa87676);
    const Color boardXSaturate = colFromHex(0xd13636);
    const Color boardO = colFromHex(0x697494);
    const Color boardOSaturate = colFromHex(0x2a53c9);
    

    Font mainFont;

    // predefined
    int boardWidth = 260;
    float subBoardWidth = 80;
    Vector2 boardOffset {0, 20};
    float cellGap = 5;
    
    // calculated
    float boardGap;
    float halfWidth;
    float cellWidth;

    char currentTurn = 'x';
    bool isSelecting = true;
    

    SubBoard boards[3][3] {};

    // shapes and cached
    Vector2 dashShape[4] = {
        {0, 0.2}, {0, 0.4}, {1, 0.6}, {1, 0.8}
    };
    Vector2 crossShapeAscend[4] {
        {0.05, 1-0.1914}, {0.1914, 1-0.05}, {1-0.1914, 0.05}, {1-0.05, 0.1914}
    };
    Vector2 crossShapeDescend[4] {
        {0.05, 0.1914}, {1-0.1914, 1-0.05}, {0.1914, 0.05}, {1-0.05, 1-0.1914}
    };

public:
    // board is supposed to be centered on 0,0
    Board();

    void setFont(Font& mainFont);
    void reset();
    void draw();
    void update(Vector2& mousePos);
    Vector2 getTopLeftOfBoard();
    Vector2 getBottomLeftOfBoard();

    friend std::ostream& operator << (std::ostream& stream, const Board& board);

private:
    Rectangle getRectOfSubboard(int i, int j);
    Rectangle getRectOfCell(int parent_i, int parent_j, int i, int j);
    void drawSubBoard(int i, int j);
    void drawWinningBoardX(Rectangle rect);
    void drawWinningBoardO(Rectangle rect);
    void drawWinningBoardD(Rectangle rect);
    void drawInformation();
    void scaleShape(Vector2* points, int numPoints, float scale);

    void updateMouseInput(Vector2& mousePos);
    void handleMouseClick(Vector2& mousePos);
    bool selectBoard(Vector2& mousePos);
    bool activateCell(Vector2& mousePos, int i, int j, Index& cellPicked);
    Index getActiveBoard();
    char checkSubBoardWon(SubBoard& board);
    char checkGameWon();
    void moveBoard(Index current, Index cellPicked);
    void makeSelecting();
    void dbg_cycleCell(int boardi, int boardj, int celli, int cellj);
};



// std::ostream& operator << (std::ostream& stream, const SubBoard& subBoard);
