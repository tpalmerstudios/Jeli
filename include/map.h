#ifndef MAP_H
#define MAP_H

#include <cstdlib>

class Map
{
    public:
	size_t w, h;

	Map ();
	int get (const size_t iX, const size_t iY) const;
	bool isEmpty (const size_t iX, const size_t iY) const;
	size_t getArea () { return w * h; }
	size_t getW () { return w; }
	size_t getH () { return h; }
	// Add a default spawn spot in each map?
};

#endif // MAP_H

