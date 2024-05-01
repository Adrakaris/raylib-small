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

constexpr uint32_t _mask_r = 0xff000000;
constexpr uint32_t _mask_g = 0x00ff0000;
constexpr uint32_t _mask_b = 0x0000ff00;
constexpr uint32_t _mask_a = 0x000000ff;

// convert RGB (A = 255)
inline Color colFromHex(std::uint32_t hexCode) {
    // assuming input of the form #(00)RRGGBB rather than #RRGGBBAA
    unsigned char red = (unsigned char)((hexCode & _mask_g) >> 16);
    unsigned char green = (unsigned char)((hexCode & _mask_b) >> 8);
    unsigned char blue = (unsigned char)((hexCode & _mask_a) >> 0);
    return Color {red, green, blue, 255};
}

// convert RGBA
inline Color colFromHexAlpha(std::uint32_t hexCode) {
    unsigned char red = (unsigned char)((hexCode & _mask_r) >> 24);
    unsigned char green = (unsigned char)((hexCode & _mask_g) >> 16);
    unsigned char blue = (unsigned char)((hexCode & _mask_b) >> 8);
    unsigned char alpha = (unsigned char)(hexCode & _mask_a);
    return Color {red, green, blue, alpha};
}

// color definitions

const Color textColorDark {210, 210, 210, 255};
const Color BG = colFromHex(0x2e2e2e);
const Color BGTrans = colFromHexAlpha(0x3e3e3ebb);
const Color button = colFromHexAlpha(0x5b5b61aa);
const Color button_active = colFromHex(0x5b5b61);
const Color green = colFromHex(0x00ff00);


