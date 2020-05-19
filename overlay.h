#ifndef OVERLAY_H
#define OVERLAY_H

struct Overlay
{
		size_t offsetX, offsetY;
		size_t h, w;
		std::vector<uint32_t> canvas;
}; // Overlay

#endif // OVERLAY_H

