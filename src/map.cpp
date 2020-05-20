#include <cassert>
#include <cstdlib>

#include "map.h"

static const char map [] = "0000111111110000"
			   "1              0"
			   "1      11111   0"
			   "1     0        0"
			   "0     0  1110000"
			   "0     1        0"
			   "0   10000      0"
			   "0   1   11100  0"
			   "1   0   0      0"
			   "1   0   1  00000"
			   "0       1      0"
			   "0       1      0"
			   "0       0      0"
			   "0 0000000      0"
			   "0              0"
			   "0001111111100000";

// Initialize a Map with w and h to 16
Map::Map () : w (16), h (16)
{
	// Make sure the map size is equal to w * h
	assert (sizeof (map) == (w * h) + 1);
}

int Map::get (const size_t iX, const size_t iY) const
{
	// Ensure the size of the map is the size of w * h.
	// Also that the coordinates are within the boundaries of the map
	assert (iX < w && iY < h && sizeof (map) == (w * h) + 1);
	// Subtracting 0 converts the char to an int
	// Returns what number is at that location.
	return map [iX + (iY * w)] - '0';
}

bool Map::isEmpty (const size_t iX, const size_t iY) const
{
	// Ensure the size of the map is the size of w * h.
	// Also that the coordinates are within the boundaries of the map
	assert (iX < w && iY < h && sizeof (map) == (w * h) + 1);
	// Subtracting 0 converts the char to an int
	// Returns what number is at that location.
	return map [iX + (iY * w)] == ' ';
}

