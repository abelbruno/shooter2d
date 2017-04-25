#ifndef __SPRITEFONT_H__
#define __SPRITEFONT_H__

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

class SpriteFont
{
    private:
        std::string m_fileName;
        FT_Library  m_library;
        FT_Face     m_face;
        float m_fontSize;
        GLuint m_textureObj;
        GLenum m_textureTarget;

        void initialize();

    public:
        SpriteFont(const std::string &fileName);
        virtual ~SpriteFont();

        FT_Bitmap* getBitmap(char c);
        FT_Bitmap* getBitmap(int fontSize, char c);
        GLuint getTexObject() {return m_textureObj;}
        GLenum getTexTarget() {return m_textureTarget;}
        int getAdvanceX() {return m_face->glyph->advance.x >> 6;}
        int getAdvanceY() {return m_face->glyph->advance.y >> 6;}
        void setFontSize(float fontSize) {m_fontSize = fontSize;}
};

#endif // __SPRITEFONT_H__
