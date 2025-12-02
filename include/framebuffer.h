#include <cstdint>
#include <cstdlib>
#include <vector>

#include "geo-prims.h"

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

/**
 * @brief Lightweight pixel container used for all on-screen drawing.
 *
 * FrameBuffer owns a contiguous RGBA buffer and provides tiny helper
 * routines for plotting pixels, clearing the screen, and drawing the simple
 * geometric primitives that other systems rely on (e.g. the mini-map overlay
 * and sky/ground fills).
 */
class FrameBuffer
{
    private:
        size_t w, h;

    public:
        /// Raw RGBA pixel buffer sized to w * h.
        std::vector<uint32_t> img;

        /**
         * @brief Return a copy of the backing pixel buffer.
         */
        std::vector<uint32_t> getImg () { return img; }
        /**
         * @brief Current framebuffer width in pixels.
         */
        size_t getW () { return w; }
        /**
         * @brief Current framebuffer height in pixels.
         */
        size_t getH () { return h; }
        /**
         * @brief Set framebuffer width. Callers must resize img themselves.
         */
        void setW (size_t wide) { w = wide; }
        /**
         * @brief Set framebuffer height. Callers must resize img themselves.
         */
        void setH (size_t height) { h = height; }

        /**
         * @brief Alpha-blend a primitive's coordinates on top of the buffer.
         * @param coords Flattened list of x/y pairs produced by a geo primitive.
         * @param color  RGBA color to blend onto the destination pixels.
         */
        void drawOver (std::vector<int> coords, uint32_t color);

        /**
         * @brief Fill the entire buffer with a solid color.
         */
        void clear (const uint32_t color);
        /**
         * @brief Safely fetch a pixel at (x, y).
         */
        uint32_t getPixel (const size_t x, const size_t y);
        /**
         * @brief Plot a pixel at (iX, iY) without clipping.
         */
        void setPixel (const size_t iX, const size_t iY, const uint32_t color);
        /**
         * @brief Draw a filled triangle directly into the buffer.
         */
        void drawTriangle (const int x1,
                           const int y1,
                           const int x2,
                           const int y2,
                           const int x3,
                           const int y3,
                           const uint32_t color);
        /**
         * @brief Draw a filled polygon produced by the geometry helpers.
         */
        void drawPolygon (Polygon poly);
        /**
         * @brief Check whether a coordinate lies inside the buffer bounds.
         */
        bool isPixel (const int x, const int y) const;
};

#endif // FRAMEBUFFER_H

