#pragma once 

#include <raylib.h>
#include <cstdint>

// screen coordinate scale (coordinate values from top to bottom)
const float SCALE = 60.0f;

// colour util functions
Color colourFromHex(std::uint32_t hexCode);


// colours
const Color BG = {240, 240, 235, 255};



