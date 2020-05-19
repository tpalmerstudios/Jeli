#include <cmath>
#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

#include "framebuffer.h"
#include "utils.h"

// Place a single pixel in the current frame
void FrameBuffer::setPixel (const size_t iX, const size_t iY, const uint32_t color)
{
		//assert (img.size () == (w * h) && (iX < w) && (iY < h));
		assert (img.size () == (w * h));
		assert (iX < w);
		assert (iY < h);
		img [iX + (iY * w)] = color;
}

// Given a coordinate on output image and dimensions and a color
// Call setPixel () and fill in the rectangle on a frame
void FrameBuffer::drawRectangle (const size_t rectX, const size_t rectY, const size_t rectW, const size_t rectH, const uint32_t color)
{
		assert (img.size () == (w * h));
		for (size_t i = 0; i < rectW; ++i)
		{
				for (size_t j = 0; j < rectH; ++j)
				{
						size_t cx = rectX + i;
						size_t cy = rectY + j;
						if (cx < w && cy < h)
								setPixel (cx, cy, color);
				}
		}
}

// Fill the entire frame with one color
void FrameBuffer::clear (const uint32_t color)
{
		img = std::vector<uint32_t> (w * h, color);
}

void FrameBuffer::drawCircle (const int x, const int y, const size_t radius, const uint32_t color)
{
		for (float angle = 0; angle < 2 * M_PI; angle += M_PI / (2 * radius * M_PI))
		{
				for (float t = 0; t < radius; ++t)
				{
						float fillX = x + (t * cos (angle));
						float fillY = y + (t * sin (angle));
						if (int (fillX) > -1 && int (fillY) > -1 && size_t (fillX) < w && size_t (fillY) < h)
								setPixel (size_t (fillX), size_t (fillY) , color);
						else
								continue;
				}
		}
}

