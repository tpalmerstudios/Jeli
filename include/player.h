#ifndef PLAYER_H
#define PLAYER_H

struct Player
{
	float x, y;
	float angle;
	float fov;
	int turn, walk;
	int horizon;
	// horizon1, horizon2 and set the horizon line based off those two.
	// Build atan angle possibly
};

#endif // PLAYER_H

