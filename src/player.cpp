#include "player.h"
#include <iostream>

void Player::initTurn (int dir)
{
	assert (dir <= 1 && dir >= -1);
	angle += float (dir) * 0.05;
}
void Player::initMove (int dir)
{
	assert (dir <= 1 && dir >= -1);
	x += dir * cos (angle) * 0.1;
	y += dir * sin (angle) * 0.1;
	std::cout << x << " " << y << std::endl;
}

void Player::moveLoc (int dir, float *targetX, float *targetY)
{
	assert (dir <= 1 && dir >= -1);
	float tX = (x + dir * cos (angle) * 0.1);
	float tY = (y + dir * sin (angle) * 0.1);
	*targetX = tX;
	*targetY = tY;
}

Player::Player (float iX, float iY, float iAngle, float iFov, int iHorizon)
    : x (iX), y (iY), angle (iAngle), fov (iFov), horizon (iHorizon)
{
}

void Player::spawn (float iX, float iY, float iAngle, float iFov, int iHorizon)
{
	// i just stands for input btw. (Input X)
	x	= iX;
	y	= iY;
	angle	= iAngle;
	fov	= iFov;
	horizon = iHorizon;
}

// Somehow I want a default constructor of player with a sane spawn point and
// angle. Once I get into altitude I can figure out sane horizons (almost always
// height / 2)
