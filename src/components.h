// game components
// YH 2024-05-01

#pragma once 

#include <raylib.h>
#include "util.h"

#pragma region buttons_and_switches

/*
I intend to reuse these later, and so we need buttons which support drawing textures, 
and buttons which are just rectangles. Hence the abstract buttons.
*/


class AbstractSwitch {
protected:
    // onClick is a callback function pointer
    bool switched;
    MouseButton clickButton;


public:
    // can be set to on by default
    AbstractSwitch(MouseButton clickButton, bool startTrue = false) {
        this->clickButton = clickButton;
        this->switched = startTrue;
    }
    virtual void update(Vector2 mousePos) = 0;
    virtual void draw() = 0;
    bool getState() { return switched; }
};


// A button that is dislpayed using default draw functionality as a rectangle
// you will have to track the activation of the button yourself using its
// bool getState() method because callbacks are difficult in C++
// note: have to inherit abstractswitch as public to get access to its methods
class RectButton : public AbstractSwitch {
private:
    Color offColour;
    Color hoverColour;
    Color pressColour; 
    Rectangle rect;
    float roundedness;
    float segments;
    bool hover = false;
    bool down = false;

public:
    // this button does support rounded rectangles, if roundedness is set above zero
    RectButton(MouseButton clickButton, Rectangle rect, 
               Color offColour, Color hoverColour, Color pressColour, 
               float roundedness = 0, int segments = 8);
    void update(Vector2 mousePos) override;
    void draw() override;
};




#pragma endregion


