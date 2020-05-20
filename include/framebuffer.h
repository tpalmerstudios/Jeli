#include <cstdlib>
#include <vector>

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

struct FrameBuffer
{
	size_t w, h;
	std::vector<uint32_t> img;

	void clear (const uint32_t color);
	void setPixel (const size_t iX, const size_t iY, const uint32_t color);
	void drawRectangle (const size_t rectX,
			    const size_t rectY,
			    const size_t rectW,
			    const size_t rectH,
			    const uint32_t color);
	void drawTriangle (const int x1,
			   const int y1,
			   const int x2,
			   const int y2,
			   const int x3,
			   const int y3,
			   const uint32_t color);
	void drawCircle (const int x,
			 const int y,
			 const size_t radius,
			 const uint32_t color);
	void drawLine (const int x1,
		       const int y1,
		       const int x2,
		       const int y2,
		       const uint32_t color);
	bool isPixel (const int x, const int y) const;
};

#endif // FRAMEBUFFER_H

