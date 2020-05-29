#include <cassert>
#include <cmath>
#ifndef PLAYER_H
#define PLAYER_H

struct Player
{
	float x, y;
	float angle;
	float fov;
	int turn, walk;
	int horizon;
	// float angle;
	void stopTurn () { turn = 0; }
	void stopMove () { walk = 0; }
	void initTurn (int dir)
	{
		assert (dir <= 1 && dir >= -1);
		angle += float (dir) * 0.05;
	}
	void initMove (int dir)
	{
		assert (dir <= 1 && dir >= -1);
		float tempX = x + dir * cos (angle) * 0.1;
		float tempY = y + dir * sin (angle) * 0.1;
		// Test if its in the bounds of the map
		// use gs.map.isEmpty() to see if he can be there
		// if (int (newX) >= 0 && int (newX) < int (gs.map.w) &&
		//    int (newY) >= 0 && int (newY) < int (gs.map.h) &&
		//    gs.map.isEmpty (newX, newY))
		//{
		//	gs.player.x = newX;
		//	gs.player.y = newY;
		//} // walking
		x = tempX;
		y = tempY;
	}
};

#endif // PLAYER_H

