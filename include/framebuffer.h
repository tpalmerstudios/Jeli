#include <cstdint>
#include <cstdlib>
#include <vector>

#include "geo-prims.h"

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

struct FrameBuffer
{
	size_t w, h;
	std::vector<uint32_t> img;

	void clear (const uint32_t color);
	void setPixel (const size_t iX, const size_t iY, const uint32_t color);
	void drawRectangle (Rectangle rect);
	void drawTriangle (const int x1,
			   const int y1,
			   const int x2,
			   const int y2,
			   const int x3,
			   const int y3,
			   const uint32_t color);
	void drawCircle (Circle circle);
	void drawLine (const int x1,
		       const int y1,
		       const int x2,
		       const int y2,
		       const uint32_t color);
	void drawPolygon (Polygon poly);
	bool isPixel (const int x, const int y) const;
};

#endif // FRAMEBUFFER_H

