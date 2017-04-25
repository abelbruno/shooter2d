#ifndef __TEXTURE2D_H__
#define __TEXTURE2D_H__

#include <iostream>
#include <string>
#include <GL/glew.h>

#include "lodepng.h"
#include "game_util.h"

class Texture2D
{
    private:
        std::string m_fileName;
        GLenum m_textureTarget;
        GLuint  m_textureObj;
        std::vector<unsigned char> m_pixels;

        unsigned int m_width;
        unsigned int m_height;
        int m_x;
        int m_y;

       void load();

    public:
        Texture2D(const std::string& fileName);
        virtual ~Texture2D();

        void draw();
        void draw(Vector2 dest);
        void draw(Rect source, Rect dest);

        int getWidth() {return (int)m_width;}
        int getHeight() {return (int)m_height;}

        void setX(int x) {m_x = x;}
        void setY(int y) {m_y = y;}
        void moveX(int x) {m_x += x;}
        void moveY(int y) {m_y += y;}

        unsigned char getPixel(int idx) {return m_pixels[idx];}
};

#endif // __TEXTURE2D_H__
