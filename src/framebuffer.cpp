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

// Given a coordinate on output image and dimensions and a color
// Call setPixel () and fill in the rectangle on a frame
void FrameBuffer::drawRectangle (Rectangle rect)
{
	assert (img.size () == (w * h));
	size_t rw      = rect.getBX () - rect.getAX ();
	size_t rh      = rect.getBY () - rect.getAY ();
	uint32_t color = rect.getColor ();
	int x	       = rect.getAX ();
	int y	       = rect.getAY ();
	for (size_t i = 0; i < rw; ++i)
	{
		for (size_t j = 0; j < rh; ++j)
			setPixel (x + i, y + j, color);
	}
}

// Fill the entire frame with one color
void FrameBuffer::clear (const uint32_t color)
{
	img = std::vector<uint32_t> (w * h, color);
}

// Based on Bresenham's Line Algorithm (integer)
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

void FrameBuffer::drawCircle (Circle circle)
{
	int x	       = circle.getX ();
	int y	       = circle.getY ();
	size_t rad     = circle.getRad ();
	uint32_t color = circle.getColor ();
	if (rad == 0 && x < int (w) && y < int (w))
		setPixel (circle.getX (), circle.getY (), circle.getColor ());
	for (size_t i = 1; i < rad; ++i)
	{
		int offX	= 0;	  // offset of origin (called cx)
		int offY	= i;	  // offset of origin (called cy)
		int sX	= 1;	  // step X
		int sY	= -2 * i; // step Y
		int determinant = 1 - i;  // (called result or dp)
		while (offX < offY)
		{
			if (determinant >= 0)
			{
				offY--;
				sY += 2;
				determinant += sY;
			}
			// On wikipedia I saw a circle with gaps in it, it was
			// discussing this algorithm, and several articles I
			// read about this algorithm have it wrong.... This next
			// block should be in an else block. Otherwise you'll
			// have to deal with it as I did
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

void FrameBuffer::drawTriangle (const int x1,
				const int y1,
				const int x2,
				const int y2,
				const int x3,
				const int y3,
				uint32_t color)
{
	/*drawLine (x1, y1, x2, y2, color);
	drawLine (x2, y2, x3, y3, color);
	drawLine (x3, y3, x1, y1, color);*/
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
