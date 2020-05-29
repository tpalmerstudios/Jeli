#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

#include "framebuffer.h"
#include "geo-prims.h"
#include "utils.h"
// Place a single pixel in the current frame
void FrameBuffer::setPixel (const size_t iX,
			    const size_t iY,
			    const uint32_t color)
{
	// assert (img.size () == (w * h) && (iX < w) && (iY < h));
	assert (img.size () == (w * h));
	if (isPixel (int (iX), int (iY)))
		img [iX + (iY * w)] = color;
}
uint32_t FrameBuffer::getPixel (const size_t x, const size_t y)
{
		assert (img.size () == (w * h));
		if (x < w && y < h)
				return img [x + (y * w)];
		else
				return packColor (255, 255, 255);
}

bool FrameBuffer::isPixel (const int x, const int y) const
{
	return (x < int (w) && y < int (h) && x >= 0 && y >= 0);
}

// Fill the entire frame with one color
void FrameBuffer::clear (const uint32_t color)
{
	img = std::vector<uint32_t> (w * h, color);
}

void FrameBuffer::drawTriangle (const int x1,
				const int y1,
				const int x2,
				const int y2,
				const int x3,
				const int y3,
				uint32_t color)
{
}
// add a polygon structure with vertex vector and a count of vertex and find the
// smallest and largest of x and y
void FrameBuffer::drawPolygon (Polygon poly)
{
	const int ends	 = poly.count ();
	const int smallX = poly.smallestX ();
	const int largeX = poly.largestX ();
	const int smallY = poly.smallestY ();
	const int largeY = poly.largestX ();
	float testX, testY;
	for (testX = smallX; testX < largeX; ++testX)
	{
		// if (testX < 0)
		//	continue;
		for (testY = smallY; testY < largeY; ++testY)
		{
			// if (testY < 0)
			//	continue;
			bool oddNodes = true;
			int i, j = ends - 1;

			for (i = 0; i < ends; ++i)
			{
				if (((poly.getY (i) < testY &&
				      poly.getY (j) >= testY) ||
				     (poly.getY (j) < testY &&
				      poly.getY (i) >= testY)) &&
				    (poly.getX (i) <= testX ||
				     poly.getX (j) <= testX))
				{
					if (poly.getX (i) +
						    (testY - poly.getY (i)) /
							    (poly.getY (j) -
							     poly.getY (i)) *
							    (poly.getX (j) -
							     poly.getX (i)) <
					    testX)
					{
						oddNodes = !oddNodes;
					}
				} // y is between two coords and x is greater
				  // than both coords (why does that work?
				  // shouldn't the x also be between the
				  // coords?)
				j = i;
			} // go through nodes
			if (!oddNodes)
			{
				setPixel (testX, testY, poly.getColor ());
			} // Color Pixel
		}	  // Y to test
	}		  // X to test
}

void FrameBuffer::drawOver (std::vector <int> coord, uint32_t color)
{
		if (coord.size () % 2)
				return;
		for (size_t i = 0; i < coord.size (); i += 2)
		{
				uint32_t bgColor = getPixel (coord [i], coord [i + 1]);
				setPixel (coord [i], coord [i + 1], overlay (bgColor, color));
		}
}
