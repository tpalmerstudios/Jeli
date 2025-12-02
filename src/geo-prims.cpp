#include <cstdint>
#include <vector>

#include <geo-prims.h>

int Rectangle::getAX () const
{
	return (origin.getX () < end.getX ()) ? origin.getX () : end.getX ();
}
int Rectangle::getAY () const
{
	return (origin.getY () < end.getY ()) ? origin.getY () : end.getY ();
}
int Rectangle::getBX () const
{
	return (end.getX () > origin.getX ()) ? end.getX () : origin.getX ();
}
int Rectangle::getBY () const
{
	return (end.getY () > origin.getY ()) ? end.getY () : origin.getY ();
}
void Rectangle::draw ()
{
        coord.clear ();
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
void Triangle::flatTop (int ax, int ay, int bx, int by, int cx, int cy)
{
	float iSlope1 = ((float) (cx - ax)) / ((float) (cy - ay));
	float iSlope2 = ((float) (cx - bx)) / ((float) (cy - by));
	float closeX  = (float) cx;
	float farX    = (float) cx;

        for (int row = cy; row > ay; --row)
        {
                Line line ((int) closeX, row, (int) farX, row);
                const std::vector<int> &lineCoords = line.getCoords ();
                coord.insert (
                        coord.end (), lineCoords.begin (), lineCoords.end ());
                closeX -= iSlope1;
                farX -= iSlope2;
        }
}
void Triangle::flatBottom (int ax, int ay, int bx, int by, int cx, int cy)
{
	// This makes the world go round.
	float iSlope1 = ((float) (bx - ax)) / ((float) (by - ay));
	float iSlope2 = ((float) (cx - ax)) / ((float) (cy - ay));
	float closeX  = (float) ax;
	float farX    = (float) ax;

        for (int row = ay; row <= by; ++row)
        {
                Line line ((int) closeX, row, (int) farX, row);
                const std::vector<int> &lineCoords = line.getCoords ();
                coord.insert (
                        coord.end (), lineCoords.begin (), lineCoords.end ());
                closeX += iSlope1;
                farX += iSlope2;
        }
}

void Triangle::draw ()
{
	coord.clear ();
	int ax, ay, bx, by, cx, cy;
	if (getAY () <= getBY () && getAY () <= getCY ())
	{
		// If A is smallest
		ax = getAX ();
		ay = getAY ();
		if (getBY () <= getCY ())
		{
			bx = getBX ();
			by = getBY ();
			cx = getCX ();
			cy = getCY ();
		}
		else
		{
			bx = getCX ();
			by = getCY ();
			cx = getBX ();
			cy = getBY ();
		}
	}
	else if (getBY () <= getAY () && getBY () <= getCY ())
	{
		// If  b is smallest
		ax = getBX ();
		ay = getBY ();
		if (getAY () <= getCY ())
		{
			bx = getAX ();
			by = getAY ();
			cx = getCX ();
			cy = getCY ();
		}
		else
		{
			bx = getCX ();
			by = getCY ();
			cx = getAX ();
			cy = getAY ();
		}
	}
	else
	{
		ax = getCX ();
		ay = getCY ();
		if (getAY () <= getBY ())
		{
			bx = getAX ();
			by = getAY ();
			cx = getBX ();
			cy = getBY ();
		}
		else
		{
			bx = getBX ();
			by = getBY ();
			cx = getAX ();
			cy = getAY ();
		}
	}
	if (by == cy)
	{
		flatBottom (ax, ay, bx, by, cx, cy);
	}
	else if (ay == by)
	{
		flatTop (ax, ay, bx, by, cx, cy);
	}
	else
	{
		// It appears this following line is the issue
		int dx = (int) (ax + ((float) ((float) (by - ay) /
					       (float) (cy - ay))) *
					     (cx - ax));

		int dy = by;
		flatTop (ax, ay, bx, by, dx, dy);
		flatBottom (bx, by, dx, dy, cx, cy);
	}
	// Get triangle min and max x and why
	// Should be y^ but I ain't fixing it
}

void Circle::draw ()
{
        coord.clear ();
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
        coord.clear ();
        int ax = origin.getX ();
	int ay = origin.getY ();
	int bx = end.getX ();
	int by = end.getY ();
	// Cant find definition? Its in geo-prims.h
	if (ay == by)
	{
		if ((bx - ax) > 0)
		{
			for (int i = (ax < 0) ? 0 : ax; i < bx; ++i)
			{
				coord.push_back (i);
				coord.push_back (ay);
			}
		}
		else
		{
			for (int i = (bx < 0) ? 0 : bx; i < ax; ++i)
			{
				coord.push_back (i);
				coord.push_back (ay);
			}
		}
	}
	else if (ax == bx)
	{
		if ((by - ay) > 0)
		{
			for (int i = (ay < 0) ? 0 : ay; i < by; ++i)
			{
				coord.push_back (ax);
				coord.push_back (i);
			}
		}
		else
		{
			for (int i = (by < 0) ? 0 : by; i < ay; ++i)
			{
				coord.push_back (ax);
				coord.push_back (i);
			}
		}
	}
	else if (abs (by - ay) < abs (bx - ax))
	{
		if (ax > bx)
		{
			// plotLineLow
			// TODO: fix this bullshit
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

			for (int fillX = (bx < 0) ? 0 : bx; fillX < ax; ++fillX)
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

			for (int fillX = (ax < 0) ? 0 : ax; fillX < bx; ++fillX)
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

			for (int fillY = (by < 0) ? 0 : by; fillY < ay; ++fillY)
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

			for (int fillY = (ay < 0) ? 0 : ay; fillY < by; ++fillY)
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

