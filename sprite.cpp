#include <cstdlib>
#include "sprite.h"

bool Sprite::operator < (const Sprite& s) const
{
		return playerDist > s.playerDist;
}

