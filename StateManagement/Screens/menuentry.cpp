#include "menuentry.h"

MenuEntry::MenuEntry(const std::string &title)
{
    m_string       = title;
    m_fontSize     = 1.0f;
    m_minFontSize  = 1.0f;
    m_maxFontSize  = 1.7f;
    m_incFontValue = 0.05f;
    m_signal       = 1.0f;
    m_updateTime   = 30.0f;
    m_oldGameTime  = 0.0f;
    m_isSelected   = false;
    m_isVertical   = true;
}

MenuEntry::MenuEntry(const std::string &title, bool isVertical)
{
    m_string       = title;
    m_fontSize     = 1.0f;
    m_minFontSize  = 1.0f;
    m_maxFontSize  = 1.7f;
    m_incFontValue = 0.05f;
    m_signal       = 1.0f;
    m_updateTime   = 30.0f;
    m_oldGameTime  = 0.0f;
    m_isSelected   = false;

    m_isVertical = isVertical;
}

MenuEntry::~MenuEntry()
{
    //dtor
}

void
MenuEntry::update(float gameTime)
{
    if (gameTime - m_oldGameTime < m_updateTime)
        return;

    if (m_isSelected)
    {
        if (m_fontSize < m_minFontSize)
            m_signal = 1;

         if (m_fontSize > m_maxFontSize)
            m_signal = -1;

        m_fontSize += m_signal * m_incFontValue;
    }
    else
    {
        if (m_fontSize > m_minFontSize)
            m_fontSize -= m_incFontValue;
    }

    m_oldGameTime = gameTime;
}

void
MenuEntry::draw(SpriteFont *font, Vector2 position, Color3d color)
{
    //if (m_isVertical)
    //    SpriteBatch::DrawString(font, m_fontSize, m_string, position, color);
    //else
        //SpriteBatch::DrawString2(font, m_fontSize, m_string, position, color);
        SpriteBatch::DrawStringCentralizedXY(font, m_fontSize, m_string, position, color);
}

void
MenuEntry::reset()
{
    m_fontSize = m_minFontSize;
    m_isSelected = false;
}
