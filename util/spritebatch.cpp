#include "spritebatch.h"

SpriteBatch::SpriteBatch()
{
    //ctor
}

SpriteBatch::~SpriteBatch()
{
    //dtor
}

void
SpriteBatch::DrawString(SpriteFont* font, const std::string& chars, Vector2 pos, Color3d color)
{
    FT_Bitmap *bitmap;

    GLuint texture = font->getTexObject();
    GLenum target  = font->getTexTarget();

    unsigned char *data = new unsigned char[4*(10000)];
    unsigned char value;

    for (int i = 0; i < chars.length(); i++)
    {
        bitmap = font->getBitmap(chars.at(i));

        for (int i = 0; i < bitmap->rows; i++)
            for (int j = 0; j < bitmap->width ; j++)
            {
                value = bitmap->buffer[i*bitmap->width + j];

                data[4*(i*bitmap->width + j) + 0] = color.R;
                data[4*(i*bitmap->width + j) + 1] = color.G;
                data[4*(i*bitmap->width + j) + 2] = color.B;
                data[4*(i*bitmap->width + j) + 3] = value;
            }

        glBindTexture(target, texture);
        glTexImage2D(target, 0, GL_RGBA, bitmap->width, bitmap->rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameterf(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBegin(GL_QUADS);
            glTexCoord2d(0.0,0.0); glVertex2d(pos.x, pos.y + bitmap->rows);
            glTexCoord2d(1.0,0.0); glVertex2d(pos.x + bitmap->width, pos.y + bitmap->rows);
            glTexCoord2d(1.0,1.0); glVertex2d(pos.x + bitmap->width, pos.y);
            glTexCoord2d(0.0,1.0); glVertex2d(pos.x, pos.y);
        glEnd();

        glBindTexture(target, 0);

        pos.x += font->getAdvanceX();
    }

    delete [] data;
}

void
SpriteBatch::DrawString(SpriteFont* font, float scale, const std::string& chars, Vector2 pos, Color3d color)
{
    FT_Bitmap *bitmap;

    GLuint texture = font->getTexObject();
    GLenum target  = font->getTexTarget();

    unsigned char *data = new unsigned char[4*(10000)];
    unsigned char value;

    for (int i = 0; i < chars.length(); i++)
    {
        bitmap = font->getBitmap(chars.at(i));

        for (int i = 0; i < bitmap->rows; i++)
            for (int j = 0; j < bitmap->width ; j++)
            {
                value = bitmap->buffer[i*bitmap->width + j];

                data[4*(i*bitmap->width + j) + 0] = color.R;
                data[4*(i*bitmap->width + j) + 1] = color.G;
                data[4*(i*bitmap->width + j) + 2] = color.B;
                data[4*(i*bitmap->width + j) + 3] = value;
            }

        glBindTexture(target, texture);
        glTexImage2D(target, 0, GL_RGBA, bitmap->width, bitmap->rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameterf(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glBegin(GL_QUADS);
            glTexCoord2d(0.0,0.0); glVertex2d(pos.x, pos.y + bitmap->rows*scale);
            glTexCoord2d(1.0,0.0); glVertex2d(pos.x + bitmap->width*scale, pos.y + bitmap->rows*scale);
            glTexCoord2d(1.0,1.0); glVertex2d(pos.x + bitmap->width*scale, pos.y);
            glTexCoord2d(0.0,1.0); glVertex2d(pos.x, pos.y);
        glEnd();

        glBindTexture(target, 0);

        pos.x += font->getAdvanceX()*scale;
    }

    delete [] data;
}

void
SpriteBatch::DrawString2(SpriteFont* font, float scale, const std::string& chars, Vector2 pos, Color3d color)
{
    FT_Bitmap *bitmap;

    GLuint texture = font->getTexObject();
    GLenum target  = font->getTexTarget();

    unsigned char *data = new unsigned char[4*(10000)];
    unsigned char value;

    for (int i = 0; i < chars.length(); i++)
    {
        bitmap = font->getBitmap(chars.at(i));

        for (int i = 0; i < bitmap->rows; i++)
            for (int j = 0; j < bitmap->width ; j++)
            {
                value = bitmap->buffer[i*bitmap->width + j];

                data[4*(i*bitmap->width + j) + 0] = color.R;
                data[4*(i*bitmap->width + j) + 1] = color.G;
                data[4*(i*bitmap->width + j) + 2] = color.B;
                data[4*(i*bitmap->width + j) + 3] = value;
            }

        glBindTexture(target, texture);
        glTexImage2D(target, 0, GL_RGBA, bitmap->width, bitmap->rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameterf(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        if (i == 0)
        {
            pos.x -=  (int)(font->getAdvanceX()*scale * chars.length())/2;
            pos.y -=  (int)(bitmap->rows*scale/2);
        }

        glBegin(GL_QUADS);
            glTexCoord2d(0.0,0.0); glVertex2d(pos.x, pos.y + bitmap->rows*scale);
            glTexCoord2d(1.0,0.0); glVertex2d(pos.x + bitmap->width*scale, pos.y + bitmap->rows*scale);
            glTexCoord2d(1.0,1.0); glVertex2d(pos.x + bitmap->width*scale, pos.y);
            glTexCoord2d(0.0,1.0); glVertex2d(pos.x, pos.y);
        glEnd();

        glBindTexture(target, 0);

        pos.x += font->getAdvanceX()*scale;
    }

    delete [] data;
}


void
SpriteBatch::DrawStringCentralizedXY(SpriteFont* font, float scale, const std::string& chars, Vector2 pos, Color3d color)
{
    FT_Bitmap *bitmap;

    float total_x = 0;
    float max_height = -1;

    for (int i = 0; i < chars.length(); i++)
    {
        bitmap = font->getBitmap(chars.at(i));

        total_x += font->getAdvanceX()*scale;

        if (bitmap->rows > max_height)
            max_height = bitmap->rows;
    }

    pos.x -= total_x / 2.0f;
    pos.y -= (int)(max_height * scale / 2.0f);

    DrawString(font, scale, chars, pos, color);
}
