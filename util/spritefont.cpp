#include "spritefont.h"

SpriteFont::SpriteFont(const std::string &fileName)
{
    m_fileName = fileName;
    m_fontSize = 24.0f;
    m_textureTarget = GL_TEXTURE_2D;

    initialize();
}

SpriteFont::~SpriteFont()
{
    glDeleteTextures(1, &m_textureObj);
}

void
SpriteFont::initialize()
{
    glGenTextures(1, &m_textureObj);

    FT_Init_FreeType( &m_library );
    FT_New_Face( m_library, m_fileName.c_str(), 0, &m_face );
    FT_Set_Char_Size(m_face, 0, m_fontSize*64, 71.23, 71.23);
}

FT_Bitmap*
SpriteFont::getBitmap(char c)
{
    FT_UInt glyph_index = FT_Get_Char_Index( m_face, c );

    FT_Load_Glyph( m_face, glyph_index, FT_LOAD_DEFAULT );

    /* convert to an anti-aliased bitmap */
    FT_Render_Glyph( m_face->glyph, FT_RENDER_MODE_NORMAL );

    return &(m_face->glyph->bitmap);
}

FT_Bitmap*
SpriteFont::getBitmap(int fontSize, char c)
{
    m_fontSize = fontSize;
    FT_Set_Char_Size(m_face, 0, m_fontSize*64, 71.23, 71.23);

    return getBitmap(c);
}
