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
void render (FrameBuffer &fb,
	     Map &map,
	     Player &player,
	     std::vector<Sprite> &sprites,
	     Texture &texWalls,
	     Texture &texMonsters);
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

void drawSky (const GameState &gs, FrameBuffer &fb)
{
	Rectangle rect;
	rect.setAX (0);
	rect.setAY (0);
	rect.setBX (fb.getW ());
	rect.setBY (gs.player.horizon);
	rect.setColor (packColor (180, 180, 255));
	fb.drawRectangle (rect);
	// fb.drawTriangle (200, 200, 600, 400, 400, 800, packColor (255, 0,
	// 0));
}

void drawMap (const GameState &gs,
	      FrameBuffer &fb,
	      const size_t cellW,
	      const size_t cellH)
{
	Rectangle mapSquare;
	mapSquare.setAX (0);
	mapSquare.setAY (0);
	mapSquare.setBX (cellW * gs.map.w);
	mapSquare.setBY (cellH * gs.map.h);
	mapSquare.setColor (packColor (170, 255, 170));
	fb.drawRectangle (mapSquare);
	for (size_t j = 0; j < gs.map.h; ++j)
	{
		for (size_t i = 0; i < gs.map.w; ++i)
		{
			if (gs.map.isEmpty (i, j))
				continue;
			size_t rectX = i * cellW;
			size_t rectY = j * cellH;
			Rectangle wall;
			wall.setAX (rectX);
			wall.setAY (rectY);
			wall.setBX (rectX + cellW);
			wall.setBY (rectY + cellH);
			wall.setColor (packColor (0, 0, 0));
			fb.drawRectangle (wall);
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
		fb.drawRectangle (obj);
	} // show monsters / sprites
	mapPositionAngle (gs.player.x,
			  gs.player.y,
			  gs.player.angle,
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
	fb.clear (packColor (255, 255, 255)); // clear screen
	/*std::vector <int> coords = { 1, 1, 300, 1, 280, 75, 800, 430, 200,
	430}; Polygon poly; poly.setColor (packColor (0, 0, 255)); if
	(poly.setVertexes(coords) != int (coords.size ())) std::cout << " You
	fucked up!\n"; fb.drawPolygon (poly);*/
	const size_t rectW =
		(fb.getW () / 4) / gs.map.w; // set width of rectangle
	const size_t rectH = (fb.getH () / 3) / gs.map.h; // set height of
	// rectangle
	// The sky!
	drawSky (gs, fb);
	// The grass
	Rectangle grass;
	grass.setAX (0);
	grass.setAY (gs.player.horizon);
	grass.setBX (fb.getW ());
	grass.setBY (fb.getH ());
	grass.setColor (packColor (70, 255, 70));
	fb.drawRectangle (grass);

	std::vector<float> depthBuffer (fb.getW (), 1e3);
	for (size_t i = 0; i < fb.getW (); ++i)
	{
		// Actual ray casting starting with left side.
		// Actual math is basing this off of angle minus
		// half the field of view plus the current ray angle
		float angle = gs.player.angle - (gs.player.fov / 2) +
			      (gs.player.fov * i) / float (fb.getW ());
		for (float t = 0; t < 15; t += 0.014)
		{
			float x = gs.player.x + (t * cos (angle));
			float y = gs.player.y + (t * sin (angle));
			// If its a " " in game map, go on, otherwise we're
			// going to go to the next ray
			if (gs.map.isEmpty (x, y))
				continue;
			size_t texID = gs.map.get (x, y);
			assert (texID < gs.texWalls.count);
			float dist	= t * cos (angle - gs.player.angle);
			depthBuffer [i] = dist;
			size_t columnHeight =
				floor (float (fb.getH ()) / dist);
			int xTexCoord = wallXTexCoord (x, y, gs.texWalls);
			std::vector<uint32_t> column =
				gs.texWalls.getScaledColumn (
					texID, xTexCoord, columnHeight);
			int pixX = i;
			for (size_t j = 0; j < columnHeight; ++j)
			{
				// Origin of the columns... floor doesn't seem
				// to do well
				int pixY = j + gs.player.horizon -
					   (columnHeight / 2);
				if (pixY >= 0 && pixY < int (fb.getH ()))
					fb.setPixel (pixX, pixY, column [j]);
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
	drawMap (gs, fb, rectW, rectH);
} // render ()

void mapPositionAngle (float x,
		       float y,
		       float angle,
		       const Map &map,
		       FrameBuffer &fb,
		       const uint32_t color)
{
	const size_t rectW = (fb.getW () / 4) / map.w;
	const size_t rectH = (fb.getH () / 3) / map.h;
	float loop	   = 0;
	for (float nAngle = (angle - M_PI) - (M_PI / 8);
	     nAngle <= (angle - M_PI) + (M_PI / 6);
	     nAngle += (M_PI / 4) * loop)
	{
		loop += .005;
		for (float j = 0; j < 1; j += 0.01)
		{
			float fillX = x + (j * cos (nAngle));
			float fillY = y + (j * sin (nAngle));
			fb.setPixel (fillX * rectW, fillY * rectH, color);
		} // draw line of angle
	}	  // Go through angles
}

void drawSprite (FrameBuffer &fb,
		 const Sprite &sprite,
		 const std::vector<float> &depthBuffer,
		 const Player &player,
		 const Texture &texSprites)
{
	// Absolute direction from player to sprite in radians
	float toSpriteAngle = atan2 (sprite.y - player.y, sprite.x - player.x);
	while (toSpriteAngle - player.angle > M_PI)
		toSpriteAngle -= 2 * M_PI;
	while (toSpriteAngle - player.angle < -M_PI)
		toSpriteAngle += 2 * M_PI;

	size_t spriteDispSize = std::min (
		1000, static_cast<int> (fb.getH () / sprite.playerDist));
	// Adjust if removing displayed map
	int offsetX = (toSpriteAngle - player.angle) * fb.getW () +
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

