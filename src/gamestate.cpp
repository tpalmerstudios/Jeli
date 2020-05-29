#include "render.h"

GameState::GameState (Map nMap,
		      Player nPlayer,
		      std::vector<Sprite> nMonsters,
		      std::string nTexWalls,
		      std::string nTexMonst)
    : texWalls (nTexWalls), texMonsters (nTexMonst)
{
	map	 = nMap;
	player	 = nPlayer;
	monsters = nMonsters;
}
void GameState::spawn (int height)
{
	int x = 0;
	int y = 0;
	int horizon;
	float angle, fov;
	// Do I need to check in both loops if equal to zero as both are set at
	// same time? Or how should I break out of loop
	for (size_t tY = 0; y == 0 && tY < map.getH (); ++tY)
	{
		for (size_t tX = 0; x == 0 && tX < map.getW (); ++tX)
		{
			if (map.isEmpty (tX, tY))
			{
				x = tX;
				y = tY;
			}
		}
	}
	// 2 issues:
	// 1) I have no access to FrameBuffer from here
	// 		// Dirty fix add a param with my height
	// 2) How am I supposed to call this. Rework my GS init
	// 3)
	horizon = height / 2;
	fov	= M_PI / 3.;
	angle	= fov / 2;
	player.spawn (x + 0.5, y + 0.5, angle, fov, horizon);
}
