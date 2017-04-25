#ifndef __SPRITEBATCH_H__
#define __SPRITEBATCH_H__

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "game_util.h"
#include "spritefont.h"

class SpriteBatch
{
    public:
        SpriteBatch();
        virtual ~SpriteBatch();

        static void DrawString(SpriteFont* font, const std::string& chars, Vector2 pos, Color3d color);
        static void DrawString(SpriteFont* font, float fontSize, const std::string& chars, Vector2 pos, Color3d color);
        static void DrawString2(SpriteFont* font, float scale, const std::string& chars, Vector2 pos, Color3d color);
        static void DrawStringCentralizedXY(SpriteFont* font, float scale, const std::string& chars, Vector2 pos, Color3d color);
};

#endif // __SPRITEBATCH_H__
