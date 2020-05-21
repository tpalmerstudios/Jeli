#include <cstdint>
#include <cstdlib>
#include <vector>

#include "geo-prims.h"

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class FrameBuffer
{
    private:
	size_t w, h;

    public:
	std::vector<uint32_t> img;

	std::vector<uint32_t> getImg () { return img;}
	size_t getW () { return w; }
	size_t getH () { return h; }
	void setW (size_t wide) { w = wide; }
	void setH (size_t height) { h = height; }

	void clear (const uint32_t color);
	uint32_t getPixel (const size_t x, const size_t y);
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
	void drawLine (Line line);
	void drawPolygon (Polygon poly);
	bool isPixel (const int x, const int y) const;
};

#endif // FRAMEBUFFER_H

