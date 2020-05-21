#include <cstdint>
#include <cstdlib>
#include <vector>

#ifndef GEO_PRIMS_H
#define GEO_PRIMS_H

class Point
{
    private:
	int x, y;

    public:
	int getX () { return x; }
	int getY () { return y; }
	void setX (int setX) { x = setX; }
	void setY (int setY) { y = setY; }
};

class Polygon
{
    private:
	std::vector<Point> vertex;
	uint32_t color;

    public:
	float getX (int vert) { return float (vertex [vert].getX ()); }
	float getY (int vert) { return float (vertex [vert].getY ()); }
	uint32_t getColor () { return color; }
	int count () { return vertex.size (); }
	void setColor (uint32_t rgba) { color = rgba; }
	int setVertexes (std::vector<int> coord);
	float smallestX ();
	float largestX ();
	float smallestY ();
	float largestY ();
};

#endif // GEO_PRIMS_H
