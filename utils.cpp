#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cassert>

#include "utils.h"

uint32_t packColor (const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
{
		return (a<<24) + (b<<16) + (g<<8) + r;
}

void unpackColor (const uint32_t &color, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a)
{
		r = (color >> 0) & 255;
		g = (color >> 8) & 255;
		b = (color >> 16) & 255;
		a = (color >> 24) & 255;
}

void dropPPMImage (const std::string filename, const std::vector<uint32_t> &image, const size_t w, const size_t h)
{
		assert (image.size () == (w * h));
		std::ofstream ppmFile (filename);
		ppmFile << "P6\n" << w << " " <<  h << "\n255\n";
		for (size_t i = 0; i < (h * w); ++i)
		{
				uint8_t r, g, b, a;
				unpackColor (image [i], r, g, b, a);
				ppmFile << static_cast<char> (r) << static_cast<char> (g) << static_cast<char> (b);
		}
		ppmFile.close ();
}
