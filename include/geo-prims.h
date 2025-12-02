#include <cstdint>
#include <cstdlib>
#include <vector>

#ifndef GEO_PRIMS_H
#define GEO_PRIMS_H

/**
 * @brief Simple geometry helpers used to draw overlays and masks.
 *
 * These primitives return flattened coordinate lists that FrameBuffer can
 * quickly blend. They intentionally avoid heavy dependencies so newcomers can
 * explore basic rasterization concepts.
 */
class Point
{
    private:
        int x, y;

    public:
        int getX () const { return x; }
        int getY () const { return y; }
        void setX (int setX) { x = setX; }
        void setY (int setY) { y = setY; }
        Point (int a, int b)
        {
                x = a;
                y = b;
        }
        Point () {}
};

/**
 * @brief Discrete circle represented by precomputed perimeter points.
 */
class Circle
{
    private:
        Point origin;
        size_t radius;
        uint32_t color;
        std::vector<int> coord;

    public:
        uint32_t getColor () const { return color; }
        void setColor (uint32_t rgba) { color = rgba; }

        int getX () const { return origin.getX (); }
        int getY () const { return origin.getY (); }

        void setX (int setX) { origin.setX (setX); }
        void setY (int setY) { origin.setY (setY); }

        void setRad (size_t rad) { radius = rad; }
        size_t getRad () const { return radius; }
        /**
         * @brief Populate the coord vector with perimeter pixels.
         */
        void draw ();
        /**
         * @brief Get or lazily compute the circle outline coordinates.
         */
        const std::vector<int> &getCoords ()
        {
                if (coord.empty ())
                        draw ();
                return coord;
        }
        Circle () {}
        ~Circle () = default;
        Circle (int x, int y, uint32_t col) : origin (x, y)
        {
                color = col;
                draw ();
        }
};

/**
 * @brief Axis-aligned rectangle helper used by overlays.
 */
class Rectangle
{
    private:
        Point origin;
        Point end;
        uint32_t color;
        std::vector<int> coord;

    public:
        uint32_t getColor () const { return color; }
        void setColor (uint32_t rgba) { color = rgba; }

        int getAX () const;
        int getAY () const;
        int getBX () const;
        int getBY () const;

        void setAX (int setX) { origin.setX (setX); }
        void setAY (int setY) { origin.setY (setY); }
        void setBX (int setX) { end.setX (setX); }
        void setBY (int setY) { end.setY (setY); }
        /**
         * @brief Compute the rectangle outline into coord.
         */
        void draw ();
        /**
         * @brief Get or lazily compute the rectangle outline.
         */
        const std::vector<int> &getCoords ()
        {
                if (coord.empty ())
                        draw ();
                return coord;
        }
        Rectangle (int ax, int ay, int bx, int by, uint32_t col)
            : origin (ax, ay), end (bx, by)
        {
                color = col;
                draw ();
        }
        Rectangle () {}
        ~Rectangle () = default;
};

/**
 * @brief Triangle primitive with helpers for scanline rasterization.
 */
class Triangle
{
    private:
        Point a, b, c;
        uint32_t color;
        std::vector<int> coord;

    public:
        uint32_t getColor () const { return color; }
        void setColor (uint32_t rgba) { color = rgba; }

        int getAX () const { return a.getX (); }
        int getAY () const { return a.getY (); }
        int getBX () const { return b.getX (); }
        int getBY () const { return b.getY (); }
        int getCX () const { return c.getX (); }
        int getCY () const { return c.getY (); }

        void setAX (int setX) { a.setX (setX); }
        void setAY (int setY) { a.setY (setY); }
        void setBX (int setX) { b.setX (setX); }
        void setBY (int setY) { b.setY (setY); }
        void setCX (int setX) { c.setX (setX); }
        void setCY (int setY) { c.setY (setY); }

        void flatTop (int, int, int, int, int, int);
        void flatBottom (int, int, int, int, int, int);
        /**
         * @brief Build a filled triangle into the coord buffer.
         */
        void draw ();
        /**
         * @brief Access the filled triangle pixels, generating them if needed.
         */
        const std::vector<int> &getCoords ()
        {
                if (coord.empty ())
                        draw ();
                return coord;
        }
        Triangle (int ax, int ay, int bx, int by, int cx, int cy, uint32_t col)
            : a (ax, ay), b (bx, by), c (cx, cy), color (col)
        {
                draw ();
        }
        Triangle () {}
        ~Triangle () = default;
};

/**
 * @brief Arbitrary polygon described by ordered vertices.
 */
class Polygon
{
    private:
        std::vector<Point> vertex;
        uint32_t color;

    public:
        float getX (int vert) const { return float (vertex [vert].getX ()); }
        float getY (int vert) const { return float (vertex [vert].getY ()); }
        uint32_t getColor () const { return color; }
        size_t count () const { return vertex.size (); }
        void setColor (uint32_t rgba) { color = rgba; }
        int setVertexes (std::vector<int> coord);
        float smallestX ();
        float largestX ();
        float smallestY ();
        float largestY ();
};

/**
 * @brief Line segment helper used by the mini-map and debug shapes.
 */
class Line
{
    private:
        Point origin;
        Point end;
        uint32_t color;
        std::vector<int> coord;

    public:
        uint32_t getColor () const { return color; }
        void setColor (uint32_t rgba) { color = rgba; }

        int getAX () const { return origin.getX (); }
        int getAY () const { return origin.getY (); }
        int getBX () const { return end.getX (); }
        int getBY () const { return end.getY (); }

        void setAX (int setX) { origin.setX (setX); }
        void setAY (int setY) { origin.setY (setY); }
        void setBX (int setX) { end.setX (setX); }
        void setBY (int setY) { end.setY (setY); }
        /**
         * @brief Use Bresenham-style plotting to build the line coordinates.
         */
        void draw ();
        /**
         * @brief Access the plotted line pixels, generating them if necessary.
         */
        const std::vector<int> &getCoords ()
        {
                if (coord.size () < 4)
                        draw ();
                return coord;
        }
        Line (int ax, int ay, int bx, int by, uint32_t col)
            : origin (ax, ay), end (bx, by), color (col)
        {
                draw ();
        }
        Line (int ax, int ay, int bx, int by)
            : origin (ax, ay), end (bx, by)
        {
                draw ();
        }
        void reinit (int ax, int ay, int bx, int by)
        {
                        origin.setX (ax);
                        origin.setY (ay);
                        end.setX (bx);
                        end.setY (by);
                        draw ();
        }
        Line () {}
        ~Line () = default;
};

#endif // GEO_PRIMS_H
