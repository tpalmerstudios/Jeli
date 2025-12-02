#ifndef MAP_H
#define MAP_H

#include <cstdlib>

/**
 * @brief 2D grid describing the raycaster world.
 *
 * Map currently stores a small, hard-coded tile array (walls are positive
 * integers, empty cells are zero). It exposes simple helpers that make it easy
 * for collision detection and ray casting to query whether a location is
 * blocked.
 */
class Map
{
    public:
        size_t w, h;

        /**
         * @brief Construct the default map with built-in layout.
         */
        Map ();
        /**
         * @brief Fetch the raw tile value at a given coordinate.
         */
        int get (const size_t iX, const size_t iY) const;
        /**
         * @brief Check whether a map cell can be traversed.
         */
        bool isEmpty (const size_t iX, const size_t iY) const;
        /**
         * @brief Total number of tiles (width * height).
         */
        size_t getArea () { return w * h; }
        /**
         * @brief Map width in tiles.
         */
        size_t getW () { return w; }
        /**
         * @brief Map height in tiles.
         */
        size_t getH () { return h; }
        // Add a default spawn spot in each map?
};

#endif // MAP_H

