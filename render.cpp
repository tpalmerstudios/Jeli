#include <cmath>
#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>
#include <sstream>
#include <iomanip>

#include "map.h"
#include "utils.h"
#include "player.h"
#include "sprite.h"
#include "framebuffer.h"
#include "textures.h"
#include "tinyraycaster.h"

int wallXTexCoord (const float hitX, const float hitY, const Texture &texWalls);
void render (FrameBuffer &fb, Map &map, Player &player, std::vector<Sprite> &sprites, Texture &texWalls, Texture &texMonsters);
void drawSprite (FrameBuffer &fb, const Sprite &sprite, const std::vector<float> &depthBuffer, const Player &player, const Texture &texSprites);
void mapPositionAngle (float x, float y, float angle, const Map &map, FrameBuffer &fb, const uint32_t color);
void drawMap (const GameState &gs, FrameBuffer &fb, const size_t cellW, const size_t cellH);
void drawSky (const GameState &gs, FrameBuffer &fb);

void drawSky (const GameState &gs, FrameBuffer &fb)
{
		fb.drawRectangle (0, 0, fb.w, gs.player.horizon, packColor (180, 180, 255));
		fb.drawCircle (500, 200, 200, packColor (0, 255, 255));
		fb.drawCircle (900, 100, 200, packColor (0, 255, 255));
}

void drawMap (const GameState &gs, FrameBuffer &fb, const size_t cellW, const size_t cellH)
{
		fb.drawRectangle (0, 0, cellW * gs.map.w, cellH * gs.map.h, packColor (170, 255, 170));
		for (size_t j = 0; j < gs.map.h; ++j)
		{
				for (size_t i = 0; i < gs.map.w; ++i)
				{
						if (gs.map.isEmpty (i, j))
								continue;
						size_t rectX = i * cellW;
						size_t rectY = j * cellH;
						fb.drawRectangle (rectX, rectY, cellW, cellH, packColor (0, 0, 0));
				} //draw the map (x)
		} // draw the map (y)
		for (size_t i = 0; i < gs.monsters.size (); ++i)
		{
				fb.drawRectangle (gs.monsters [i].x * cellW - cellW / 2, gs.monsters [i].y * cellH - cellH / 2, cellW / 2, cellH / 2, packColor (255, 0, 0));
		} // show monsters / sprites
		mapPositionAngle (gs.player.x, gs.player.y, gs.player.angle, gs.map, fb, packColor (0, 128, 255));
}

int wallXTexCoord (const float hitX, const float hitY, const Texture &texWalls)
{
		float x = hitX - floor (hitX + 0.5);
		float y = hitY - floor (hitY + 0.5);
		int texture = x * texWalls.size; //What does this do???????????
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
		const size_t rectW = (fb.w / 4) / gs.map.w; // set width of rectangle
		const size_t rectH = (fb.h / 3) / gs.map.h; // set height of rectangle 
		// The sky!
		drawSky (gs, fb);
		// The grass
		fb.drawRectangle (0, gs.player.horizon, fb.w, fb.h - gs.player.horizon, packColor(70, 255, 70));

		std::vector<float> depthBuffer(fb.w, 1e3);
		for (size_t i = 0; i < fb.w; ++i)
		{
				// Actual ray casting starting with left side.
				// Actual math is basing this off of angle minus
				// half the field of view plus the current ray angle
				float angle = gs.player.angle - (gs.player.fov / 2) + (gs.player.fov * i) / float (fb.w);
				for (float t = 0; t < 15; t += 0.014)
				{
						float x = gs.player.x + (t * cos (angle));
						float y = gs.player.y + (t * sin (angle));
						// If its a " " in game map, go on, otherwise we're going to go to the next ray
						if (gs.map.isEmpty (x, y))
								continue;
						size_t texID = gs.map.get (x, y);
						assert (texID < gs.texWalls.count);
						float dist = t * cos (angle - gs.player.angle);
						depthBuffer [i] = dist;
						size_t columnHeight = floor ((float) fb.h / (float) dist);
						int xTexCoord = wallXTexCoord (x, y, gs.texWalls);
						std::vector<uint32_t> column = gs.texWalls.getScaledColumn (texID, xTexCoord, columnHeight);
						int pixX = i;
						for (size_t j = 0; j < columnHeight; ++j)
						{
								// Origin of the columns... floor doesn't seem to do well
								int pixY = j + gs.player.horizon - (columnHeight / 2);
								if (pixY >= 0 && pixY < (int) fb.h)
										fb.setPixel (pixX, pixY, column [j]);
						}
						break;
				} // draw out the length of the ray
		} // Ray sweeping fov
		for (size_t i = 0; i < gs.monsters.size (); ++i)
		{
				drawSprite (fb, gs.monsters [i], depthBuffer, gs.player, gs.texMonsters);
		} // Show sprites
		drawMap (gs, fb, rectW, rectH);
} //render ()

void mapPositionAngle (float x, float y, float angle, const Map &map, FrameBuffer &fb, const uint32_t color)
{
		const size_t rectW = (fb.w / 4) / map.w;
		const size_t rectH = (fb.h / 3) / map.h;
		float loop = 0;
		for (float nAngle = (angle - M_PI) - (M_PI / 8); nAngle <= (angle - M_PI) + (M_PI / 6); nAngle += (M_PI / 4) * loop)
		{
				loop += .005;
				for (float j = 0; j < 1; j += 0.01)
				{
						float fillX = x + (j * cos (nAngle));
						float fillY = y + (j * sin (nAngle));
						fb.drawRectangle (fillX * rectW, fillY * rectH, 1, 1, color);
				} // draw line of angle
		} // Go through angles
}


void drawSprite (FrameBuffer &fb, const Sprite &sprite, const std::vector<float> &depthBuffer, const Player &player, const Texture &texSprites)
{
		// Absolute direction from player to sprite in radians
		float toSpriteAngle = atan2 (sprite.y - player.y, sprite.x - player.x);
		while (toSpriteAngle  - player.angle > M_PI)
				toSpriteAngle -= 2 * M_PI;
		while (toSpriteAngle - player.angle < -M_PI)
				toSpriteAngle += 2 * M_PI;

		size_t spriteDispSize = std::min (1000, static_cast<int> (fb.h / sprite.playerDist));
		// Adjust if removing displayed map
		int offsetX = (toSpriteAngle - player.angle) * fb.w + (fb.w / 2)  - texSprites.size / 2;
		int offsetY = player.horizon - (spriteDispSize / 2);

		for (size_t loopX = 0; loopX < spriteDispSize; ++loopX)
		{
				if (offsetX + int (loopX) < 0 || offsetX + loopX >= fb.w)
						continue;
				if (depthBuffer [offsetX + loopX] < sprite.playerDist)
						continue;
				for (size_t loopY = 0; loopY < spriteDispSize; ++loopY)
				{
						if (offsetY + int (loopY) < 0 || offsetY + loopY >= fb.h)
								continue;
						uint32_t color = texSprites.get (loopX * texSprites.size /spriteDispSize, loopY * texSprites.size / spriteDispSize, sprite.texID);
						uint8_t r, g, b, a, bgR, bgG, bgB, bgA;
						unpackColor (color, r, g, b, a);
						uint32_t bgColor = fb.img [(offsetX + loopX) + ((offsetY + loopY) * fb.w)];
						unpackColor (bgColor, bgR, bgG, bgB, bgA);
						// if r,g,b are greater than the background r,g,b take the difference times the opacity and add it to the background color, otherwise subtract it
						size_t dif;
						// Red
						dif = (r - bgR) * float (a / 255);
						if ((size_t) r - (size_t) bgR > 0)
								r = ((size_t) bgR + dif > 255) ? 255 : bgR + (uint8_t) dif;
						else
								r = ((size_t) bgR - dif < 0) ? 0 : bgR - (uint8_t) dif;
						// Green
						dif = (g - bgG) * float (a / 255);
						if ((size_t) g - (size_t) bgG > 0)
								g = ((size_t) bgG + dif > 255) ? 255 : bgG + (uint8_t) dif;
						else
								g = ((size_t) bgG - dif < 0) ? 0 : bgG - (uint8_t) dif;
						// Blue
						dif = (b - bgB) * float (a / 255);
						if ((size_t) b - (size_t) bgB > 0)
								b = ((size_t) bgB + dif > 255) ? 255: bgB + (uint8_t) dif;
						else
								b = ((size_t) bgB - dif < 0) ? 0 : bgB - (uint8_t) dif;
						fb.setPixel (offsetX + loopX, offsetY + loopY, packColor (r, g, b));
				}
		}
}

