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
			int dx	  = ax - bx;	      // Delta X
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
			int dx	  = bx - ax;	      // Delta X
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
			int dx	  = ax - bx;	      // Delta X
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
			int dx	  = bx - ax;	      // Delta X
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
