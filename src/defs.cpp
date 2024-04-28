#include "defs.h"


uint32_t _mask_r = 0xff000000;
uint32_t _mask_g = 0x00ff0000;
uint32_t _mask_b = 0x0000ff00;
uint32_t _mask_a = 0x000000ff;

Color colourFromHex(std::uint32_t hexCode) {
    unsigned char red = (unsigned char)((hexCode & _mask_r) >> 24);
    unsigned char green = (unsigned char)((hexCode & _mask_g) >> 16);
    unsigned char blue = (unsigned char)((hexCode & _mask_b) >> 8);
    unsigned char alpha = (unsigned char)(hexCode & _mask_a);
    return Color {red, green, blue, alpha};
}
