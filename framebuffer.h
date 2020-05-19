#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstdlib>
#include <vector>

struct FrameBuffer
{
		size_t w, h;
		std::vector<uint32_t> img;

		void clear (const uint32_t color);
		void setPixel (const size_t iX, const size_t iY, const uint32_t color);
		void drawRectangle (const size_t rectX, const size_t rectY, const size_t rectW, const size_t rectH, const uint32_t color);
		void drawCircle (const int x, const int y, const size_t radius, const uint32_t color);
};

#endif //FRAMEBUFFER_H

