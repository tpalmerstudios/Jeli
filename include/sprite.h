#ifndef SPRITE_H
#define SPRITE_H

#include <cstdlib>

/**
 * @brief Billboards rendered after walls for enemies and objects.
 */
struct Sprite
{
        /// World-space position in map units.
        float x, y;
        /// Index into the monster texture atlas.
        size_t texID;
        /// Cached distance from player, used for painter's sorting.
        float playerDist;

        /**
         * @brief Sort sprites from farthest to nearest for correct overlap.
         */
        bool operator< (const Sprite &s) const;
};

#endif // SPRITE_H

