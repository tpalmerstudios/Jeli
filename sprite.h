#ifndef SPRITE_H
#define SPRITE_H

#include <cstdlib>

struct Sprite
{
	float x, y;
	size_t texID;
	float playerDist;
	bool operator< (const Sprite &s) const;
};

#endif // SPRITE_H

