#include "components.h"


RectButton::RectButton(MouseButton clickButton, Rectangle rect, 
                       Color offColour, Color hoverColour, Color pressColour, 
                       float roundedness, int segments) : AbstractSwitch(clickButton, false) {
    this->rect = rect;
    this->offColour = offColour;
    this->hoverColour = hoverColour;
    this->pressColour = pressColour;
    this->roundedness = roundedness;
    this->segments = segments;
}


void RectButton::update(Vector2 mousePos) {
    if (CheckCollisionPointRec(mousePos, rect)) {
        hover = true;
        down = IsMouseButtonDown(clickButton);
        switched = IsMouseButtonReleased(clickButton);
    } else {
        hover = false; 
        down = false;
    }
    
}

void RectButton::draw() {
    if (down) {
        DrawRectangleRounded(rect, roundedness, segments, pressColour);
    } else if (hover) {
        DrawRectangleRounded(rect, roundedness, segments, hoverColour);
    } else {
        DrawRectangleRounded(rect, roundedness, segments, offColour);
    }
}


// automatically turn off the switched
bool RectButton::getState() {
    bool tmp = switched;
    switched = false;
    return tmp;
}
