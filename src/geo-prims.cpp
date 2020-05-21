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
