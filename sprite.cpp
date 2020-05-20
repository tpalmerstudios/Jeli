#include "sprite.h"
#include <cstdlib>

bool Sprite::operator< (const Sprite &s) const
{
	return playerDist > s.playerDist;
}

