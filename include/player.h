#include <cassert>
#include <cmath>
#ifndef PLAYER_H
#define PLAYER_H

/**
 * @brief Represents the controllable camera within the world.
 *
 * Player tracks position, facing direction, and simple movement intent flags
 * (turn/walk). Input handling code updates these flags; the render and
 * collision systems query the resulting position and angle to drive the
 * raycaster.
 */
class Player
{
    private:
        int turn = 0;
        int walk = 0;
        float x, y;
        float angle = 0.;

    public:
        /// Horizontal field-of-view in radians.
        float fov;
        // float altitude;
        // this will be used with the algorithm to determine view point
        // though I need to add a camera header that is attached (usually) to players head
        /// Screen-space horizon line used to split sky and floor drawing.
        int horizon;
        // float tilt; // head movement LR

        /**
         * @brief Current facing angle in radians.
         */
        float getAngle () const { return angle; }
        /**
         * @brief Clear any pending turn input.
         */
        void stopTurn () { turn = 0; }
        /**
         * @brief Clear any pending walk input.
         */
        void stopMove () { walk = 0; }
        /**
         * @brief Begin turning left (-1) or right (+1).
         */
        void initTurn (int dir);
        /**
         * @brief Begin walking forward (+1) or backward (-1).
         */
        void initMove (int dir);
        /**
         * @brief Player position along the X axis.
         */
        float getX () const { return x; }
        /**
         * @brief Player position along the Y axis.
         */
        float getY () const { return y; }
        /**
         * @brief Predict a movement step without immediately applying it.
         *
         * Used by collision detection to test whether the next step would
         * intersect a wall. The proposed target coordinates are written to
         * @p targetX and @p targetY.
         */
        void moveLoc (int dir, float *targetX, float *targetY);
        // Is this dirty? It feels like I could use the constructor
        // But how do I construct from the GameState class by calling the spawn
        // function
        // I think I need the spawn function for other uses
        /**
         * @brief Initialize player position and camera configuration.
         * @param xPos Starting X coordinate (map units).
         * @param yPos Starting Y coordinate (map units).
         * @param fovRads Field of view in radians.
         * @param ang    Initial facing angle in radians.
         * @param horiz  Horizon line in screen pixels.
         */
        void spawn (float, float, float, float, int);
        Player () {}
        Player (float, float, float, float, int);
};

#endif // PLAYER_H

