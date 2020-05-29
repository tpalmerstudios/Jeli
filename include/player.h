#include <cassert>
#include <cmath>
#ifndef PLAYER_H
#define PLAYER_H

class Player
{
    private:
	int turn = 0;
	int walk = 0;
	float x, y;
	float angle = 0.;

    public:
	float fov;
	int horizon;
	// float tilt; // head movement LR
	float getAngle () const { return angle; }
	void stopTurn () { turn = 0; }
	void stopMove () { walk = 0; }
	void initTurn (int dir);
	void initMove (int dir);
	float getX () const { return x; }
	float getY () const { return y; }
	void moveLoc (int dir, float *targetX, float *targetY);
	// Is this dirty? It feels like I could use the constructor
	// But how do I construct from the GameState class by calling the spawn
	// function
	// I think I need the spawn function for other uses
	void spawn (float, float, float, float, int);
	Player () {}
	Player (float, float, float, float, int);
};

#endif // PLAYER_H

