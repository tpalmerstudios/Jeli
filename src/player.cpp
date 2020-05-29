#include "player.h"

void Player::initTurn (int dir)
{
	assert (dir <= 1 && dir >= -1);
	angle += float (dir) * 0.05;
}
void Player::initMove (int dir)
{
	assert (dir <= 1 && dir >= -1);
	float tempX = x + dir * cos (angle) * 0.1;
	float tempY = y + dir * sin (angle) * 0.1;
	// Test if its in the bounds of the map
	// use gs.map.isEmpty() to see if he can be there
	// if (int (newX) >= 0 && int (newX) < int (gs.map.w) &&
	//    int (newY) >= 0 && int (newY) < int (gs.map.h) &&
	//    gs.map.isEmpty (newX, newY))
	x = tempX;
	y = tempY;
}

Player::Player (float iX, float iY, float iAngle, float iFov, int iHorizon) : x (iX), y (iY), angle (iAngle), fov (iFov), horizon (iHorizon)
{}

void Player::spawn (float iX, float iY, float iAngle, float iFov, int iHorizon)
{
	// i just stands for input btw. (Input X)
	x	= iX;
	y	= iY;
	angle	= iAngle;
	fov	= iFov;
	horizon = iHorizon;
}
