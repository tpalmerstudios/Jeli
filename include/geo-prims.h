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

class Circle
{
    private:
	Point origin;
	size_t radius;
	uint32_t color;

    public:
	size_t getRad () { return radius; }
	uint32_t getColor () { return color; }
	int getX () { return origin.getX (); }
	int getY () { return origin.getY (); }
	void setRad (size_t rad) { radius = rad; }
	void setX (int setX) { origin.setX (setX); }
	void setY (int setY) { origin.setY (setY); }
	void setColor (uint32_t rgba) { color = rgba; }
};

class Rectangle
{
    private:
	Point origin;
	Point end;
	uint32_t color;

    public:
	uint32_t getColor () { return color; }
	void setColor (uint32_t rgba) { color = rgba; }

	int getLeft ();
	int getTop ();
	int getRight ();
	int getBottom ();

	void setLeft (int setX) { origin.setX (setX); }
	void setTop (int setY) { origin.setY (setY); }
	void setRight (int setX) { end.setX (setX); }
	void setBottom (int setY) { end.setY (setY); }
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
