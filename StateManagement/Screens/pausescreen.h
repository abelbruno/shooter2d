#ifndef __PAUSE_SCREEN_H__
#define __PAUSE_SCREEN_H__

#include <vector>
#include <iostream>

#include "screen.h"
#include "menuentry.h"
#include "../../util/game_util.h"
#include "../../util/soundfx.h"
#include "../../util/spritefont.h"

class PauseScreen : public Screen
{
    private:
        std::vector<MenuEntry *> m_menuEntries;
        Vector2 m_menuPosition;
        float m_menuInterval;
        int m_selectedEntry;
        SpriteFont *m_font;
        SoundFX *m_soundFX;
        SoundFX *m_itemMenuFX;
        SoundFX *m_selectItemMenuFX;

        //Input
        bool *m_keyStates;
        std::vector<bool> m_oldKeyStates;

    public:
        PauseScreen(unsigned int windowW, unsigned int windowH, bool *keyStates): Screen(windowW, windowH)
        {
            m_font = new SpriteFont("Content/pixel_classic.ttf");
            m_keyStates = keyStates;
            m_menuPosition = Vector2(352, 170);
            m_menuInterval = 110.0f;

            m_oldKeyStates.resize(256);

            load();
        }

        virtual ~PauseScreen();

        void initialize();
        void update(float gameTime);
        void draw();
        void load();
        void unload();

        void upMenu();
        void downMenu();
        void selectMenu();
};

#endif // __PAUSE_SCREEN_H__
