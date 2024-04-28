#pragma once 

#include <raylib.h>
#include <iostream>
#include <format>

#include "util.h"


// use 'X' and 'O' directly
struct SubBoard {
    char values[3][3] = {0};
    bool isHovered = false;
    bool isActive = false;
    char isWon = 0;
};


class Board {

private:
    const Color baseColor = colFromHex(0x3e3e3e);
    const Color subColor = colFromHex(0x323236);
    const Color subColorActive = colFromHex(0x4b4b50);
    const Color subColorHovered = colFromHex(0x36363a);

    const Color cellBlank = colFromHex(0x5b5b61);
    const Color cellX = colFromHex(0xc96767);
    const Color cellO = colFromHex(0x6d84c9);


    // predefined
    int boardWidth = 260;
    float subBoardWidth = 80;
    Vector2 boardOffset {0, 20};
    float cellGap = 5;
    
    // calculated
    float boardGap;
    float halfWidth;
    float cellWidth;

    float currentTurn = 'X';
    bool isSelecting = true;

    SubBoard boards[3][3] {};

public:
    // board is supposed to be centered on 0,0
    Board();

    void reset();
    void draw();
    void update(Vector2& mousePos);

    friend std::ostream& operator << (std::ostream& stream, const Board& board);

private:
    Rectangle getRectOfSubboard(int i, int j);
    Rectangle getRectOfCell(int parent_i, int parent_j, int i, int j);
    void drawSubBoard(int i, int j);
    void updateMouseInput(Vector2& mousePos);
    void handleMouseClick(Vector2& mousePos);
    bool selectBoard(Vector2& mousePos);
    void makeSelecting();
};



// std::ostream& operator << (std::ostream& stream, const SubBoard& subBoard);
