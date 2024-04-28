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
    bool isAvailable = false;
    char isWon = 0;
};


class Board {

private:
    const Color baseColor = colFromHex(0x3e3e3e);
    const Color subColor = colFromHex(0x323236);
    const Color subColorActive = colFromHex(0x4b4b50);
    const Color subColorHovered = colFromHex(0x36363a);

    int boardWidth;
    float subBoardWidth;
    Vector2 boardOffset;

    float boardGap;
    float halfWidth;

    SubBoard boards[3][3];

public:
    // board is supposed to be centered on 0,0
    Board(int boardWidth = 260, float subBoardWidth = 80, Vector2 boardOffset = Vector2 {0, 20});

    void reset();
    void draw();
    void update(Vector2& mousePos);

    friend std::ostream& operator << (std::ostream& stream, const Board& board);

private:
    Rectangle getRectOfSubboard(int i, int j);
    void drawSubBoard(int i, int j);
    void updateMouseInput(Vector2& mousePos);
    
};



// std::ostream& operator << (std::ostream& stream, const SubBoard& subBoard);
