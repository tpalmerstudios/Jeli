#ifndef TEXTURES_H
#define TEXTURES_H

#include <cstdint>
#include <string>
#include <vector>

/**
 * @brief Loads and samples horizontally packed texture atlases.
 *
 * The engine expects a single image that contains N square textures placed side
 * by side. Texture exposes helpers for loading that image, sampling an
 * individual texel, and building a vertically scaled column suited for wall or
 * sprite rendering.
 */
class Texture
{
    public:
        size_t imgWidth, imgHeight;
        size_t count, size;
        std::vector<uint32_t> img;

        /**
         * @brief Load a texture atlas from disk.
         * @param filename Path to a PNG compatible with stb_image.
         */
        Texture (const std::string filename);
        /**
         * @brief Sample a single texel from a specific texture slice.
         * @param iX X coordinate inside the square slice.
         * @param iY Y coordinate inside the square slice.
         * @param texID Zero-based index of the slice to sample.
         */
        uint32_t get (const size_t iX,
                      const size_t iY,
                      const size_t texID) const; // Get a pixel from texture
        /**
         * @brief Extract and scale a vertical column for rendering.
         * @param texID Index of the slice to sample from the atlas.
         * @param texCoord Horizontal coordinate within the slice.
         * @param columnHeight Desired height of the scaled column in pixels.
         */
        std::vector<uint32_t> getScaledColumn (const size_t texID,
                                               const size_t texCoord,
                                               const size_t columnHeight)
                const; // Retrieve a column from texID and scale it correctly
};

#endif // TEXTURES_H

