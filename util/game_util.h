#ifndef __GAME_UTIL_H__
#define __GAME_UTIL_H__

#include <cstdlib>

namespace Keys
{
    //======================================================
    // Using GLFW keyboard interface
    // obs: some characters do not correspond to the Unicode standard
    //======================================================
    enum
    {
        ESC   = 256,
        Space = 32,
        A     = 65,
        D     = 68,
        P     = 80,
        S     = 83,
        W     = 87
    };

    /*/======================================================
    // Using Unicode standard
    //======================================================

    enum
    {
        ESC   = 27,
        Space = 32,
        a     = 97,
        d     = 100,
        p     = 112,
        s     = 115,
        w     = 119
    };

    //========================================================*/
}

struct Vector2
{
    float x;
    float y;

    Vector2(float x=0, float y=0): x(x), y(y)
    {
    }

    Vector2& operator=(const Vector2& v)
    {
        x = v.x;
        y = v.y;
        return *this;
    }

    Vector2 operator+(const Vector2& v) const
    {
        return Vector2(x + v.x, y + v.y);
    }

    Vector2 operator-(const Vector2& v) const
    {
        return Vector2(x - v.x, y - v.y);
    }

    bool operator==(const Vector2& v) const
    {
        return (x == v.x && y == v.y);
    }

};

struct Rect
{
    float x;
    float y;
    float width;
    float height;

    Rect(float x=0,float y=0,float width=0,float height=0): x(x),y(y),width(width),height(height)
    {
    }

    Rect& operator=(const Rect &r)
    {
        x = r.x;
        y = r.y;
        width  = r.width;
        height = r.height;
        return *this;
    }

    bool valueInRange(int value, int min, int max)
    {
        return (value >= min) && (value <=max);
    }

    bool intersects(const Rect &r)
    {
        bool xOverlap = valueInRange(x, r.x, r.x + r.width) ||
                        valueInRange(r.x, x, x + width);

        bool yOverlap = valueInRange(y, r.y, r.y + r.height) ||
                        valueInRange(r.y, y, y + height);

        return xOverlap && yOverlap;
    }
};

struct Color3f
{
    float R;
    float G;
    float B;

    Color3f(float R, float G, float B): R(R), G(G), B(B)
    {
    }
};

struct Color3d
{
    unsigned char R;
    unsigned char G;
    unsigned char B;

    Color3d(unsigned char R, unsigned char G, unsigned char B): R(R), G(G), B(B)
    {
    }
};

#endif // __GAME_UTIL_H__
