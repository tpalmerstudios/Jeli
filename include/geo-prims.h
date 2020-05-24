#include <cstdint>
#include <cstdlib>
#include <iostream>
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
	Point (int a, int b)
	{
		x = a;
		y = b;
	}
	Point () {}
};

class Circle
{
    private:
	Point origin;
	size_t radius;
	uint32_t color;
	std::vector<int> coord;

    public:
	uint32_t getColor () { return color; }
	void setColor (uint32_t rgba) { color = rgba; }

	int getX () { return origin.getX (); }
	int getY () { return origin.getY (); }

	void setX (int setX) { origin.setX (setX); }
	void setY (int setY) { origin.setY (setY); }

	void setRad (size_t rad) { radius = rad; }
	size_t getRad () { return radius; }
	void draw ();
	std::vector<int> getCoords ()
	{
		if (coord.empty ())
			draw ();
		return coord;
	}
	Circle () {}
	~Circle () { coord.clear (); }
	Circle (int x, int y, uint32_t col) : origin (x, y)
		{
				color = col;
				draw ();
		}
};

class Rectangle
{
    private:
	Point origin;
	Point end;
	uint32_t color;
	std::vector<int> coord;

    public:
	uint32_t getColor () { return color; }
	void setColor (uint32_t rgba) { color = rgba; }

	int getAX ();
	int getAY ();
	int getBX ();
	int getBY ();

	void setAX (int setX) { origin.setX (setX); }
	void setAY (int setY) { origin.setY (setY); }
	void setBX (int setX) { end.setX (setX); }
	void setBY (int setY) { end.setY (setY); }
	void draw ();
	std::vector<int> getCoords ()
	{
		if (coord.empty ())
			draw ();
		return coord;
	}
	Rectangle (int ax, int ay, int bx, int by, uint32_t col)
	    : origin (ax, ay), end (bx, by)
	{
		color = col;
		draw ();
	}
	Rectangle () {}
	~Rectangle () { coord.clear (); }
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

class Line
{
    private:
	Point origin;
	Point end;
	uint32_t color;
	std::vector<int> coord;

    public:
	uint32_t getColor () { return color; }
	void setColor (uint32_t rgba) { color = rgba; }

	int getAX () { return origin.getX (); }
	int getAY () { return origin.getY (); }
	int getBX () { return end.getX (); }
	int getBY () { return end.getY (); }

	void setAX (int setX) { origin.setX (setX); }
	void setAY (int setY) { origin.setY (setY); }
	void setBX (int setX) { end.setX (setX); }
	void setBY (int setY) { end.setY (setY); }
	void draw ();
	std::vector<int> getCoords ()
	{
		if (coord.size () < 4)
			draw ();
		return coord;
	}
	Line (int ax, int ay, int bx, int by, uint32_t col)
	    : origin (ax, ay), end (bx, by)
	{
		color = col;
		draw ();
	}
	Line () {}
	~Line () { coord.clear (); }
};

#endif // GEO_PRIMS_H
