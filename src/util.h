#pragma once 

#include <raylib.h>
#include <cstdint>

// world coordinate scale (coordinate values from top to bottom)
const float SCALE = 320.0f;

// screen definitoins
enum ScreenType {
    TITLE, GAME
};

// abstract class
class Screen {
protected:
    ScreenType* screenRef;  // this isnt very OOP but ... ah whatever

public:
    Screen(ScreenType* screenRef) {
        this->screenRef = screenRef;
    };
    virtual void update(float dt) = 0;  // pure virutal function -- a function which MUST be overridden
    virtual void draw() = 0;
};

// colour util functions

// convert RGB (A = 255)
Color colFromHex(std::uint32_t hexCode);
// convert RGBA
Color colFromHexAlpha(std::uint32_t hexCode);

// color definitions

const Color textColorDark {210, 210, 210, 255};

