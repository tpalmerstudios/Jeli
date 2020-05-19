#ifndef MAP_H
#define MAP_H

#include <cstdlib>

struct Map
{
		size_t w, h;
		Map ();
		int get (const size_t iX, const size_t iY) const;
		bool isEmpty (const size_t iX, const size_t iY) const;
};

#endif //MAP_H

