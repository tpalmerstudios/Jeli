#include <cstdint>
#include <vector>

#include <geo-prims.h>

int Rectangle::getAX ()
{
	return (origin.getX () < end.getX ()) ? origin.getX () : end.getX ();
}
int Rectangle::getAY ()
{
	return (origin.getY () < end.getY ()) ? origin.getY () : end.getY ();
}
int Rectangle::getBX ()
{
	return (end.getX () > origin.getX ()) ? end.getX () : origin.getX ();
}
int Rectangle::getBY ()
{
	return (end.getY () > origin.getY ()) ? end.getY () : origin.getY ();
}
void Rectangle::draw ()
{
	const size_t rw = getBX () - getAX ();
	const size_t rh = getBY () - getAY ();
	const int cx	= getAX ();
	const int cy	= getAY ();
	for (size_t i = 0; i < rw; ++i)
	{
		for (size_t j = 0; j < rh; ++j)
		{
			coord.push_back (cx + i);
			coord.push_back (cy + j);
		}
	}
}

void Triangle::draw ()
{
		int ax = getAX ();
		int ay = getAY ();
		int bx = getBX ();
		int by = getBY ();
		int cx = getCX ();
		int cy = getCY ();
		// Get triangle min and max x and why
		// Should be y^ but I ain't fixing it
		scanLine (ax, ay, bx, by);
		scanLine
}

void Circle::draw ()
{
	int x	   = getX ();
	int y	   = getY ();
	size_t rad = getRad ();

	if (rad == 0)
	{
		coord.push_back (x);
		coord.push_back (y);
	}
	for (size_t i = 1; i < rad; ++i)
	{
		int offX	= 0;	  // offset of origin (called cx)
		int offY	= i;	  // offset of origin (called cy)
		int sX		= 1;	  // step X
		int sY		= -2 * i; // step Y
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
			 * or if I can skip it so I can save on those precious
			 * precious cpu cycles
			 * ***********************/
			coord.push_back (x + offX);
			coord.push_back (y + offY);
			coord.push_back (x - offX);
			coord.push_back (y + offY);
			coord.push_back (x + offX);
			coord.push_back (y - offY);
			coord.push_back (x - offX);
			coord.push_back (y - offY);

			coord.push_back (x + offY);
			coord.push_back (y + offX);
			coord.push_back (x - offY);
			coord.push_back (y + offX);
			coord.push_back (x + offY);
			coord.push_back (y - offX);
			coord.push_back (x - offY);
			coord.push_back (y - offX);
		}
		coord.push_back (x);
		coord.push_back (y + i);
		coord.push_back (x);
		coord.push_back (y - i);
		coord.push_back (x + i);
		coord.push_back (y);
		coord.push_back (x - i);
		coord.push_back (y);
	}
}

int Polygon::setVertexes (std::vector<int> coord)
{
	if (coord.size () % 2)
		return -1;
	vertex.resize (coord.size () / 2);
	Point p;
	for (size_t i = 0; i < coord.size (); i += 2)
	{
		p.setX (coord [i]);
		p.setY (coord [i + 1]);
		vertex.push_back (p);
	}
	return vertex.size ();
}

// Finds the smallest x coordinate in the polygon
float Polygon::smallestX ()
{
	int smallest;
	for (size_t i = 0; i < vertex.size (); ++i)
	{
		if (vertex [i].getX () < smallest)
			smallest = vertex [i].getX ();
	}
	return float (smallest);
}

// Finds the largest x coordinate in the polygon
float Polygon::largestX ()
{
	int largest;
	for (size_t i = 0; i < vertex.size (); ++i)
	{
		if (vertex [i].getX () > largest)
			largest = vertex [i].getX ();
	}
	return float (largest);
}

// Finds the smallest y coordinate in the polygon
float Polygon::smallestY ()
{
	int smallest;
	for (size_t i = 0; i < vertex.size (); ++i)
	{
		if (vertex [i].getY () < smallest)
			smallest = vertex [i].getY ();
	}
	return float (smallest);
}

// finds the largest y coordinate in the polygon
float Polygon::largestY ()
{
	int largest;
	for (size_t i = 0; i < vertex.size (); ++i)
	{
		if (vertex [i].getY () > largest)
			largest = vertex [i].getY ();
	}
	return float (largest);
}
void Line::draw ()
{
	int ax = origin.getX ();
	int ay = origin.getY ();
	int bx = end.getX ();
	int by = end.getY ();
	// Cant find definition? Its in geo-prims.h
	if (abs (by - ay) < abs (bx - ax))
	{
		if (ax > bx)
		{
			// plotLineLow
			int dx	  = ax - bx; // Delta X
			int dy	  = ay - by; // Delta Y
			int yMove = 1;
			if (dy < 0)
			{
				yMove = -1;
				dy    = -dy;
			}
			int diff  = 2 * dy - dx;
			int fillY = by;

			for (int fillX = bx; fillX < ax; ++fillX)
			{
				coord.push_back (fillX);
				coord.push_back (fillY);
				if (diff > 0)
				{
					fillY += yMove;
					diff -= 2 * dx;
				}
				diff += 2 * dy;
			}
		}
		else
		{
			// plotLineLow
			int dx	  = bx - ax; // Delta X
			int dy	  = by - ay; // Delta Y
			int yMove = 1;
			if (dy < 0)
			{
				yMove = -1;
				dy    = -dy;
			}
			int diff  = 2 * dy - dx;
			int fillY = ay;

			for (int fillX = ax; fillX < bx; ++fillX)
			{
				coord.push_back (fillX);
				coord.push_back (fillY);
				if (diff > 0)
				{
					fillY += yMove;
					diff -= 2 * dx;
				}
				diff += 2 * dy;
			}
		}
	}
	else
	{
		if (ay > by)
		{
			// plotline high
			int dx	  = ax - bx; // Delta X
			int dy	  = ay - by; // Delta Y
			int xMove = 1;
			if (dx < 0)
			{
				xMove = -1;
				dx    = -dx;
			}
			int diff  = 2 * dx - dy;
			int fillX = bx;

			for (int fillY = by; fillY < ay; ++fillY)
			{
				coord.push_back (fillX);
				coord.push_back (fillY);
				if (diff > 0)
				{
					fillX += xMove;
					diff -= 2 * dy;
				}
				diff += 2 * dx;
			}
		}
		else
		{
			// plotline high
			int dx	  = bx - ax; // Delta X
			int dy	  = by - ay; // Delta Y
			int xMove = 1;
			if (dx < 0)
			{
				xMove = -1;
				dx    = -dx;
			}
			int diff  = 2 * dx - dy;
			int fillX = ax;

			for (int fillY = ay; fillY < by; ++fillY)
			{
				coord.push_back (fillX);
				coord.push_back (fillY);
				if (diff > 0)
				{
					fillX += xMove;
					diff -= 2 * dy;
				}
				diff += 2 * dx;
			}
		}
	}
}
