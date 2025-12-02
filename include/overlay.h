#include <cstdint>
#include <vector>

#ifndef OVERLAY_H
#define OVERLAY_H

/**
 * @brief Off-screen buffer that can be composited onto the main framebuffer.
 *
 * Overlays are used for HUD-style elements such as the mini-map. They carry a
 * small canvas plus the screen offset where they should be blended.
 */
struct Overlay
{
        /// X/Y offsets into the destination framebuffer.
        std::size_t offsetX, offsetY;
        /// Overlay dimensions in pixels.
        std::size_t h, w;
        /// Pixel buffer holding overlay contents.
        std::vector<uint32_t> canvas;
}; // Overlay

#endif // OVERLAY_H

