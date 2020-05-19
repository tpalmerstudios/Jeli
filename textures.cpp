#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "utils.h"
#include "textures.h"

Texture::Texture (const std::string filename) : imgWidth (0), imgHeight (0), count (0), size (0), img ()
{
		int nchannels = -1, w, h;
		unsigned char *pixmap = stbi_load (filename.c_str (), &w, &h, &nchannels, 0);
		if (!pixmap)
		{
				std::cerr << "Error: can not load the textures\n";
				return;
		}

		if (nchannels != 4)
		{
				std::cerr << "Error: the texture must be a 32 bit image\n";
				stbi_image_free (pixmap);
				return;
		}

		if (w != h * int (w / h))
		{
				std::cerr << "Error: the texture file must contain N square textures packed horizontally\n";
				stbi_image_free (pixmap);
				return;
		}

		count = w / h;
		size = w / count;
		imgWidth = w;
		imgHeight = h;

		img = std::vector<uint32_t> (w * h);
		for (int loopY = 0; loopY < h; ++loopY)
		{
				for (int loopX = 0; loopX < w; ++loopX)
				{
						uint8_t r = pixmap [(loopX + (loopY * w)) * 4 + 0];
						uint8_t g = pixmap [(loopX + (loopY * w)) * 4 + 1];
						uint8_t b = pixmap [(loopX + (loopY * w)) * 4 + 2];
						uint8_t a = pixmap [(loopX + (loopY * w)) * 4 + 3];
						img [loopX + (loopY * w)] = packColor (r, g, b, a);
				}
		}
		stbi_image_free (pixmap);
}

// Get the color from a position in the texture file
// Using a position and the texture ID
uint32_t Texture::get (const size_t iX, const size_t iY, const size_t texID) const
{
		assert (iX < size && iY < size && texID < count);
		return img [ iX + (texID * size) + (iY *imgWidth)];
}

// Get a column from texture file
std::vector<uint32_t> Texture::getScaledColumn (const size_t texID, const size_t texCoord, const size_t columnHeight) const
{
		assert (texCoord < size && texID < count);
		std::vector<uint32_t> column (columnHeight);
		for (size_t y = 0; y < columnHeight; ++y)
		{
				// Get the color from the texture file and place in column
				column [y] = get (texCoord, (y * size) / columnHeight, texID);
		}
		return column;
}
