#pragma once 

#include <raylib.h>
#include <raymath.h>
#include <cstdint>

// world coordinate scale (coordinate values from top to bottom)
const float SCALE = 320.0f;

// screen definitoins
enum ScreenType {
    TITLE, GAME
};

// screen class
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

// text util functions

// draw text centre-justified on the left-right -- the top-bottom is not centred!
inline void DrawCentredText(const Font& font, const char* text, Vector2 position, float fontSize, float fontSpacing, Color tint) {
    Vector2 bbox = MeasureTextEx(font, text, fontSize, fontSpacing);
    position.x -= bbox.x / 2;  // centre the text by moving the position halfway left
    DrawTextEx(font, text, position, fontSize, fontSpacing, tint);
}


// colour util functions
#pragma region colour_util_functions

constexpr uint32_t _mask_r = 0xff000000;
constexpr uint32_t _mask_g = 0x00ff0000;
constexpr uint32_t _mask_b = 0x0000ff00;
constexpr uint32_t _mask_a = 0x000000ff;

// convert RGB (A = 255)
constexpr Color colFromHex(std::uint32_t hexCode) {
    // assuming input of the form #(00)RRGGBB rather than #RRGGBBAA
    unsigned char red = (unsigned char)((hexCode & _mask_g) >> 16);
    unsigned char green = (unsigned char)((hexCode & _mask_b) >> 8);
    unsigned char blue = (unsigned char)((hexCode & _mask_a) >> 0);
    return Color {red, green, blue, 255};
}

// convert RGBA
constexpr Color colFromHexAlpha(std::uint32_t hexCode) {
    unsigned char red = (unsigned char)((hexCode & _mask_r) >> 24);
    unsigned char green = (unsigned char)((hexCode & _mask_g) >> 16);
    unsigned char blue = (unsigned char)((hexCode & _mask_b) >> 8);
    unsigned char alpha = (unsigned char)(hexCode & _mask_a);
    return Color {red, green, blue, alpha};
}

// color definitions

constexpr Color textColorDark {210, 210, 210, 255};
constexpr Color BG = colFromHex(0x2e2e2e);
constexpr Color BGTrans = colFromHexAlpha(0x3e3e3ebb);
constexpr Color button = colFromHexAlpha(0x5b5b61aa);
// this is the button hover colour
constexpr Color button_active = colFromHex(0x5b5b61);
constexpr Color green = colFromHex(0x00ff00);
constexpr Color button_down = colFromHex(0x41b812);

#pragma endregion
#pragma region Shape and TExt



// element wise multiplies an array of vector of points by scale
void scaleShape(Vector2* points, int numPoints, float scale) {
    for (int i = 0; i < numPoints; i++) {
        // std::cout << "Prev shape " << points[i].x << "," << points[i].y << "; ";
        points[i] = Vector2Scale(points[i], scale);
        // std::cout << "New shape " << points[i].x << "," << points[i].y << "; " << std::endl;
    }
}


#pragma endregion



