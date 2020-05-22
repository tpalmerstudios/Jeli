#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <string>
#include <vector>

uint32_t packColor (const uint8_t r,
		    const uint8_t g,
		    const uint8_t b,
		    const uint8_t a = 255);
void unpackColor (
	const uint32_t &color, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a);
void dropPPMImage (const std::string filename,
		   const std::vector<uint32_t> &image,
		   const size_t w,
		   const size_t h);
uint32_t overlay (const uint32_t bgColor, const uint32_t fgColor);

#endif // UTILS_H

