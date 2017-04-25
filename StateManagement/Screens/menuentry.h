#ifndef __MENU_ENTRY_H__
#define __MENU_ENTRY_H__

#include <string>
#include <iostream>

#include "../../util/game_util.h"
#include "../../util/spritebatch.h"
#include "../../util/spritefont.h"

class MenuEntry
{
    private:
        std::string m_string;
        float m_fontSize;
        float m_minFontSize;
        float m_maxFontSize;
        float m_incFontValue;
        float m_signal;
        float m_updateTime;
        float m_oldGameTime;
        bool m_isSelected;
        bool m_isVertical;

    public:
        MenuEntry(const std::string &title);
        MenuEntry(const std::string &title, bool isVertical);
        virtual ~MenuEntry();

        void update(float gameTime);
        void draw(SpriteFont *font, Vector2 position, Color3d color);

        void select() {m_isSelected = true;}
        void deselect() {m_isSelected = false;}
        void reset();
};

#endif // __MENU_ENTRY_H__
