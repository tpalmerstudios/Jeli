#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <string>
#include <vector>

/**
 * @brief Pack RGBA channels into a 32-bit integer.
 */
uint32_t packColor (const uint8_t r,
                    const uint8_t g,
                    const uint8_t b,
                    const uint8_t a = 255);
/**
 * @brief Split a packed RGBA value back into separate channels.
 */
void unpackColor (
        const uint32_t &color, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a);
/**
 * @brief Write a framebuffer image to disk as a binary PPM file.
 */
void dropPPMImage (const std::string filename,
                   const std::vector<uint32_t> &image,
                   const size_t w,
                   const size_t h);
/**
 * @brief Alpha blend a foreground pixel onto a background pixel.
 */
uint32_t overlay (const uint32_t bgColor, const uint32_t fgColor);

#endif // UTILS_H

