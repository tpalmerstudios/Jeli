#include <vector>

#include "framebuffer.h"
#include "map.h"
#include "player.h"
#include "sprite.h"
#include "textures.h"

#ifndef RENDER_H
#define RENDER_H

/**
 * @brief Aggregates the live state used by the renderer.
 *
 * GameState bundles the map, player, sprite list, and textures so that the
 * render loop and input handling can share a single lightweight structure.
 */
class GameState
{
    public:
        Map map;
        Player player;
        std::vector<Sprite> monsters;
        Texture texWalls;
        Texture texMonsters;
        /**
         * @brief Spawn the player at the first open cell and set screen params.
         * @param height Height of the output framebuffer in pixels (for horizon).
         */
        void spawn (int height);
        /**
         * @brief Construct a fully-initialized game state.
         * @param map Map to use for rendering and collision.
         * @param player Player camera instance.
         * @param sprites Initial list of monsters to render.
         * @param texName Path to wall texture atlas.
         * @param spriteTexName Path to monster texture atlas.
         */
        GameState (Map, Player, std::vector<Sprite>, std::string, std::string);

}; // gamestate

/**
 * @brief Draw a single frame using the current GameState into the framebuffer.
 */
void render (FrameBuffer &fb, const GameState &gs);

#endif // RENDER_H

