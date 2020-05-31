#include <cassert>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "framebuffer.h"
#include "geo-prims.h"
#include "map.h"
#include "player.h"
#include "sprite.h"
#include "textures.h"
#include "utils.h"

#include "render.h"

int wallXTexCoord (const float hitX, const float hitY, const Texture &texWalls);
// Can I just pass the gamestate
void render (FrameBuffer &fb, GameState &gs);
void drawSprite (FrameBuffer &fb,
		 const Sprite &sprite,
		 const std::vector<float> &depthBuffer,
		 const Player &player,
		 const Texture &texSprites);
void mapPositionAngle (float x,
		       float y,
		       float angle,
		       const Map &map,
		       FrameBuffer &fb,
		       const uint32_t color);
void drawMap (const GameState &gs,
	      FrameBuffer &fb,
	      const size_t cellW,
	      const size_t cellH);
void drawSky (const GameState &gs, FrameBuffer &fb);
void drawGround (const GameState &gs, FrameBuffer &fb);

void drawGround (const GameState &gs, FrameBuffer &fb)
{
	Rectangle rect (0,
			gs.player.horizon,
			fb.getW (),
			fb.getH (),
			packColor (70, 255, 70));
	fb.drawOver (rect.getCoords (), rect.getColor ());
}

void drawSky (const GameState &gs, FrameBuffer &fb)
{
	Rectangle rect (
		0, 0, fb.getW (), gs.player.horizon, packColor (180, 180, 255));
	fb.drawOver (rect.getCoords (), rect.getColor ());
	// fb.drawTriangle (200, 200, 600, 400, 400, 800, packColor (255, 0,
	// 0));
}

void drawMap (const GameState &gs,
	      FrameBuffer &fb,
	      const size_t cellW,
	      const size_t cellH)
{
	Rectangle mapSquare (0,
			     0,
			     cellW * gs.map.w,
			     cellH * gs.map.h,
			     packColor (170, 255, 170));
	fb.drawOver (mapSquare.getCoords (), mapSquare.getColor ());
	for (size_t j = 0; j < gs.map.h; ++j)
	{
		for (size_t i = 0; i < gs.map.w; ++i)
		{
			if (gs.map.isEmpty (i, j))
				continue;
			size_t rectX = i * cellW;
			size_t rectY = j * cellH;
			Rectangle wall (rectX,
					rectY,
					rectX + cellW,
					rectY + cellH,
					packColor (0, 0, 0));
			fb.drawOver (wall.getCoords (), wall.getColor ());
		} // draw the map (x)
	}	  // draw the map (y)
	for (size_t i = 0; i < gs.monsters.size (); ++i)
	{
		Rectangle obj;
		obj.setAX (gs.monsters [i].x * cellW - cellW / 2);
		obj.setAY (gs.monsters [i].y * cellH - cellH / 2);
		obj.setBX (gs.monsters [i].x * cellW);
		obj.setBY (gs.monsters [i].y * cellH);
		obj.setColor (packColor (255, 0, 0));
		fb.drawOver (obj.getCoords (), obj.getColor ());
	} // show monsters / sprites
	mapPositionAngle (gs.player.getX (),
			  gs.player.getY (),
			  gs.player.getAngle (),
			  gs.map,
			  fb,
			  packColor (0, 128, 255));
}

int wallXTexCoord (const float hitX, const float hitY, const Texture &texWalls)
{
	float x	    = hitX - floor (hitX + 0.5);
	float y	    = hitY - floor (hitY + 0.5);
	int texture = x * texWalls.size; // What does this do???????????
	// Possibly returns the column or row that x, y refers to
	if (std::abs (y) > std::abs (x))
		texture = y * texWalls.size;
	if (texture < 0)
		texture += texWalls.size;
	assert (texture >= 0 && texture < (int) texWalls.size);
	return texture;
}

void render (FrameBuffer &fb, const GameState &gs)
{
	fb.clear (packColor (255, 255, 255));
	drawSky (gs, fb);
	drawGround (gs, fb);
	const size_t mapW =
		(fb.getW () / 4) / gs.map.w; // set width of rectangle
	const size_t mapH = (fb.getH () / 3) / gs.map.h; // set height of

	std::vector<float> depthBuffer (fb.getW (), 1e3);
	for (size_t i = 0; i < fb.getW (); ++i)
	{
		// Actual ray casting starting with left side.
		// Actual math is basing this off of angle minus
		// half the field of view plus the current ray angle
		float angle = gs.player.getAngle () - (gs.player.fov / 2) +
			      (gs.player.fov * i) / float (fb.getW ());
		for (float t = 0; t < 15; t += 0.014)
		{
			float x = gs.player.getX () + (t * cos (angle));
			float y = gs.player.getY () + (t * sin (angle));
			// If its a " " in game map, go on, otherwise we're
			// going to go to the next ray
			if (gs.map.isEmpty (x, y))
				continue;
			size_t texID = gs.map.get (x, y);
			assert (texID < gs.texWalls.count);
			float dist = t * cos (angle - gs.player.getAngle ());
			depthBuffer [i]	    = dist;
			size_t columnHeight = floor (float (fb.getH ()) / dist);
			int xTexCoord	    = wallXTexCoord (x, y, gs.texWalls);
			std::vector<uint32_t> column =
				gs.texWalls.getScaledColumn (
					texID, xTexCoord, columnHeight);
			int pixX = i;
			for (size_t j = 0; j < columnHeight; ++j)
			{
				// Origin of the columns... floor doesn't seem
				// to do well TODO: Fix origin, columnHeigh,
				// etc.
				int pixY = j + gs.player.horizon -
					   (columnHeight / 2);
				if (pixY >= 0 && pixY < int (fb.getH ()))
					fb.setPixel (pixX, pixY, column [j]);
				// Why are there columns that are several pixels
				// wide sometimes? I don't understand
				// Like the same issue I think as this previous
				// one
			}
			break;
		} // draw out the length of the ray
	}	  // Ray sweeping fov
	for (size_t i = 0; i < gs.monsters.size (); ++i)
	{
		drawSprite (fb,
			    gs.monsters [i],
			    depthBuffer,
			    gs.player,
			    gs.texMonsters);
	} // Show sprites
	drawMap (gs, fb, mapW, mapH);
} // render ()

void mapPositionAngle (float x,
		       float y,
		       float angle,
		       const Map &map,
		       FrameBuffer &fb,
		       const uint32_t color)
{
	int ax, ay, bx, by, cx, cy;

	const size_t mapW = (fb.getW () / 4) / map.w;
	const size_t mapH = (fb.getH () / 3) / map.h;
	ax		  = mapW * (x + cos (angle));
	ay		  = mapH * (y + sin (angle));
	bx		  = mapW * (x - cos (angle - (M_PI / 6)));
	by		  = mapH * (y - sin (angle - (M_PI / 6)));
	cx		  = mapW * (x - cos (angle + (M_PI / 6)));
	cy		  = mapH * (y - sin (angle + (M_PI / 6)));
	std::cout << ax << ", " << ay << "\n" << bx << ", " << by << "\n" << cx << ", " << cy << "\n";
	Triangle trigon (ax, ay, bx, by, cx, cy, color);

	fb.drawOver (trigon.getCoords (), trigon.getColor ());
}

void drawSprite (FrameBuffer &fb,
		 const Sprite &sprite,
		 const std::vector<float> &depthBuffer,
		 const Player &player,
		 const Texture &texSprites)
{
	// Absolute direction from player to sprite in radians
	float toSpriteAngle =
		atan2 (sprite.y - player.getY (), sprite.x - player.getX ());
	while (toSpriteAngle - player.getAngle () > M_PI)
		toSpriteAngle -= 2 * M_PI;
	while (toSpriteAngle - player.getAngle () < -M_PI)
		toSpriteAngle += 2 * M_PI;

	size_t spriteDispSize = std::min (
		1000, static_cast<int> (fb.getH () / sprite.playerDist));
	// Adjust if removing displayed map
	int offsetX = (toSpriteAngle - player.getAngle ()) * fb.getW () +
		      (fb.getW () / 2) - texSprites.size / 2;
	int offsetY = player.horizon - (spriteDispSize / 2);

	for (size_t loopX = 0; loopX < spriteDispSize; ++loopX)
	{
		if (offsetX + int (loopX) < 0 || offsetX + loopX >= fb.getW ())
			continue;
		if (depthBuffer [offsetX + loopX] < sprite.playerDist)
			continue;
		for (size_t loopY = 0; loopY < spriteDispSize; ++loopY)
		{
			if (offsetY + int (loopY) < 0 ||
			    offsetY + loopY >= fb.getH ())
				continue;
			uint32_t fgColor = texSprites.get (
				loopX * texSprites.size / spriteDispSize,
				loopY * texSprites.size / spriteDispSize,
				sprite.texID);
			uint32_t bgColor =
				fb.getPixel (offsetX + loopX, offsetY + loopY);
			fb.setPixel (offsetX + loopX,
				     offsetY + loopY,
				     overlay (bgColor, fgColor));
		}
	}
}

