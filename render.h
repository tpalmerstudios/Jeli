#ifndef RENDER_H
#define RENDER_H

struct GameState
{
	Map map;
	Player player;
	std::vector<Sprite> monsters;
	Texture texWalls;
	Texture texMonsters;
}; // gamestate
void render (FrameBuffer &fb, const GameState &gs);

#endif // RENDER_H

