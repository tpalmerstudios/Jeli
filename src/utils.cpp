#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

#include "utils.h"

uint32_t
packColor (const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
{
	return (a << 24) + (b << 16) + (g << 8) + r;
}

void unpackColor (
	const uint32_t &color, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a)
{
	r = (color >> 0) & 255;
	g = (color >> 8) & 255;
	b = (color >> 16) & 255;
	a = (color >> 24) & 255;
}

void dropPPMImage (const std::string filename,
		   const std::vector<uint32_t> &image,
		   const size_t w,
		   const size_t h)
{
	assert (image.size () == (w * h));
	std::ofstream ppmFile (filename);
	ppmFile << "P6\n" << w << " " << h << "\n255\n";
	for (size_t i = 0; i < (h * w); ++i)
	{
		uint8_t r, g, b, a;
		unpackColor (image [i], r, g, b, a);
		ppmFile << static_cast<char> (r) << static_cast<char> (g)
			<< static_cast<char> (b);
	}
	ppmFile.close ();
}

uint32_t overlay (const uint32_t bgColor, const uint32_t fgColor)
{
	// if r,g,b are greater than the background r,g,b take the difference
	// times the opacity and add it to the background color, otherwise
	// subtract it
	uint8_t bgR, bgG, bgB, bgA, fgR, fgG, fgB, fgA;
	unpackColor (bgColor, bgR, bgG, bgB, bgA);
	unpackColor (fgColor, fgR, fgG, fgB, fgA);
	// Red
	size_t colorDif = (fgR - bgR) * float (fgA / 255);
	if ((size_t) fgR - (size_t) bgR > 0)
		fgR = ((size_t) bgR + colorDif > 255)
			      ? 255
			      : bgR + (uint8_t) colorDif;
	else
		fgR = ((size_t) bgR - colorDif < 0) ? 0
						    : bgR - (uint8_t) colorDif;
	// Green
	colorDif = (fgG - bgG) * float (fgA / 255);
	if ((size_t) fgG - (size_t) bgG > 0)
		fgG = ((size_t) bgG + colorDif > 255)
			      ? 255
			      : bgG + (uint8_t) colorDif;
	else
		fgG = ((size_t) bgG - colorDif < 0) ? 0
						    : bgG - (uint8_t) colorDif;
	// Blue
	colorDif = (fgB - bgB) * float (fgA / 255);
	if ((size_t) fgB - (size_t) bgB > 0)
		fgB = ((size_t) bgB + colorDif > 255)
			      ? 255
			      : bgB + (uint8_t) colorDif;
	else
		fgB = ((size_t) bgB - colorDif < 0) ? 0
						    : bgB - (uint8_t) colorDif;
	return packColor (fgR, fgG, fgB);
}
