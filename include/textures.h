#include <cstdint>
#include <string>
#include <vector>

#ifndef TEXTURES_H
#define TEXTURES_H

struct Texture
{
	size_t imgWidth, imgHeight;
	size_t count, size;
	std::vector<uint32_t> img;

	Texture (const std::string filename);
	uint32_t get (const size_t iX,
		      const size_t iY,
		      const size_t texID) const; // Get a pixel from texture
	std::vector<uint32_t> getScaledColumn (const size_t texID,
					       const size_t texCoord,
					       const size_t columnHeight)
		const; // Retrieve a column from texID and scale it correctly
};

#endif // TEXTURES_H

