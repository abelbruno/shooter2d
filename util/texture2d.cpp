#include "texture2d.h"

Texture2D::Texture2D(const std::string& fileName)
{
    m_textureTarget = GL_TEXTURE_2D;
    m_fileName = fileName;
    m_x = 0;
    m_y = 0;

    load();
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &m_textureObj);

    std::vector<unsigned char>().swap(m_pixels);
}

void
Texture2D::load()
{
    //decode
    unsigned error = lodepng::decode(m_pixels, m_width, m_height, m_fileName);

    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    glGenTextures(1, &m_textureObj);
    glBindTexture(m_textureTarget, m_textureObj);
    glTexImage2D(m_textureTarget, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_pixels.data());
    glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //delete [] data;
    std::cout << m_width << "x" << m_height << " -> " << m_textureObj << std::endl;
}

void
Texture2D::draw()
{
    glBindTexture(m_textureTarget, m_textureObj);

    glBegin(GL_QUADS);
        glTexCoord2d(0.0,0.0); glVertex2d(m_x, m_y + m_height);
        glTexCoord2d(1.0,0.0); glVertex2d(m_x + m_width, m_y + m_height);
        glTexCoord2d(1.0,1.0); glVertex2d(m_x + m_width, m_y);
        glTexCoord2d(0.0,1.0); glVertex2d(m_x, m_y);
	glEnd();

	//glBindTexture(m_textureTarget, 0);
}

void
Texture2D::draw(Vector2 dest)
{
    glBindTexture(m_textureTarget, m_textureObj);

    glBegin(GL_QUADS);
        glTexCoord2d(0.0,0.0); glVertex2d(dest.x, dest.y + m_height);
        glTexCoord2d(1.0,0.0); glVertex2d(dest.x + m_width, dest.y + m_height);
        glTexCoord2d(1.0,1.0); glVertex2d(dest.x + m_width, dest.y);
        glTexCoord2d(0.0,1.0); glVertex2d(dest.x, dest.y);
	glEnd();

	//glBindTexture(m_textureTarget, 0);
}

void
Texture2D::draw(Rect source, Rect dest)
{
    glBindTexture(m_textureTarget, m_textureObj);

    glBegin(GL_QUADS);
        glTexCoord2d(source.x/m_width, source.y/m_height);
        glVertex2d(dest.x, dest.y + dest.height);

        glTexCoord2d((source.x + source.width)/m_width,source.y/m_height);
        glVertex2d(dest.x + dest.width, dest.y + dest.height);

        glTexCoord2d((source.x + source.width)/m_width,source.height/m_height);
        glVertex2d(dest.x + dest.width, dest.y);

        glTexCoord2d(source.x/m_width, source.height/m_height);
        glVertex2d(dest.x, dest.y);
	glEnd();
}

