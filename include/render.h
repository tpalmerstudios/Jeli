#include <vector>

#include "framebuffer.h"
#include "map.h"
#include "player.h"
#include "sprite.h"
#include "textures.h"

#ifndef RENDER_H
#define RENDER_H

class GameState
{
    public:
	Map map;
	Player player;
	std::vector<Sprite> monsters;
	Texture texWalls;
	Texture texMonsters;
	void spawn (int height);
	GameState (Map, Player, std::vector<Sprite>, std::string, std::string);

}; // gamestate
void render (FrameBuffer &fb, const GameState &gs);

#endif // RENDER_H

