#pragma once 

#include <raylib.h>
#include <cstdint>

// world coordinate scale (coordinate values from top to bottom)
const float SCALE = 320.0f;

// colour util functions

// convert RGB (A = 255)
Color colFromHex(std::uint32_t hexCode);
// convert RGBA
Color colFromHexAlpha(std::uint32_t hexCode);



