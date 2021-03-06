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

class Triangle
{
    private:
	Point a, b, c;
	uint32_t color;
	std::vector<int> coord;

    public:
	uint32_t getColor () { return color; }
	void setColor (uint32_t rgba) { color = rgba; }

	int getAX () { return a.getX (); }
	int getAY () { return a.getY (); }
	int getBX () { return b.getX (); }
	int getBY () { return b.getY (); }
	int getCX () { return c.getX (); }
	int getCY () { return c.getY (); }

	void setAX (int setX) { a.setX (setX); }
	void setAY (int setY) { a.setY (setY); }
	void setBX (int setX) { b.setX (setX); }
	void setBY (int setY) { b.setY (setY); }
	void setCX (int setX) { c.setX (setX); }
	void setCY (int setY) { c.setY (setY); }

	void flatTop (int, int, int, int, int, int);
	void flatBottom (int, int, int, int, int, int);
	void draw ();
	std::vector<int> getCoords ()
	{
		if (coord.empty ())
			draw ();
		return coord;
	}
	Triangle (int ax, int ay, int bx, int by, int cx, int cy, uint32_t col)
	    : a (ax, ay), b (bx, by), c (cx, cy), color (col)
	{
		draw ();
	}
	Triangle () {}
	~Triangle () { coord.clear (); }
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
	    : origin (ax, ay), end (bx, by), color (col)
	{
		draw ();
	}
	Line (int ax, int ay, int bx, int by)
	    : origin (ax, ay), end (bx, by)
	{
		draw ();
	}
	void reinit (int ax, int ay, int bx, int by)
	{
			origin.setX (ax);
			origin.setY (ay);
			end.setX (bx);
			end.setY (by);
			draw ();
	}
	Line () {}
	~Line () { coord.clear (); }
};

#endif // GEO_PRIMS_H
