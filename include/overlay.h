#include <cstdint>
#include <vector>

#ifndef OVERLAY_H
#define OVERLAY_H

struct Overlay
{
	std::size_t offsetX, offsetY;
	std::size_t h, w;
	std::vector<uint32_t> canvas;
}; // Overlay

#endif // OVERLAY_H

