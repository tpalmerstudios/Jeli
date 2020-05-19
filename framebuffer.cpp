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
		if (isPixel (int (iX), int (iY)))
				img [iX + (iY * w)] = color;
}

bool FrameBuffer::isPixel (const int x, const int y) const
{
		return (x < int (w) && y < int (h) && x >= 0 && y >= 0);
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
		// I casted to int rather than to size_t because negative ints to size_t would give me garbage data
		if (radius == 0 && x < int (w) && y < int (w))
				setPixel (x, y, color);
		for (size_t i = 1; i < radius; ++i)
		{
				int offX = 0;				// offset of origin (called cx)
				int offY = i;				// offset of origin (called cy)
				size_t sX = 1;				// step X
				size_t sY = -2 * i;			// step Y
				int determinant = 1 - i;	// (called result or dp)
				while (offX < offY)
				{
						if (determinant >= 0)
						{
								offY--;
								sY += 2;
								determinant += sY;
						}
						else
						{
								offX++;
								sX += 2;
								determinant += sX;
						}
						/**************************
						 * Figure out if all of these points are valid!
						 * ***********************/
						setPixel (x + offX, y + offY, color);
						setPixel (x - offX, y + offY, color);
						setPixel (x + offX, y - offY, color);
						setPixel (x - offX, y - offY, color);
						setPixel (x + offY, y + offX, color);
						setPixel (x - offY, y + offX, color);
						setPixel (x + offY, y - offX, color);
						setPixel (x - offY, y - offX, color);
				}
				setPixel (x, y + i, color);
				setPixel (x, y - i, color);
				setPixel (x + i, y, color);
				setPixel (x - i, y, color);
		}
}

void FrameBuffer::drawTriangle (const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, uint32_t color)
{
		// This assumes the points are in order I think
		// And it doesn't fill it in
		// And it doesn't mean that the shape is closed either
		// This is just a shit show of a function... thanks stackoverflow 
		// Oh! and it draws a fucking rectangle
		//https://stackoverflow.com/questions/25835468/draw-a-triangle-from-scratch-given-three-points
		for (int fillX = x1; fillX <= x2; ++fillX)
		{
				for (int fillY = y1; fillY <= y2; ++fillY)
				{
						setPixel (fillX, fillY, color);
				}
		}
		for (int fillX = x2; fillX <= x3; ++fillX)
		{
				for (int fillY = y2; fillY <= y3; ++fillY)
				{
						setPixel (fillX, fillY, color);
				}
		}
		for (int fillX = x1; fillX <= x2; ++fillX)
		{
				for (int fillY = y1; fillY <= y2; ++fillY)
				{
						setPixel (fillX, fillY, color);
				}
		}
}
