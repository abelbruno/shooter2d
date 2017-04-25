#ifndef __MAINMENU_SCREEN_H__
#define __MAINMENU_SCREEN_H__

#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>

#include "screen.h"
#include "menuentry.h"
#include "../../util/game_util.h"
#include "../../util/texture2d.h"
#include "../../util/spritefont.h"
#include "../../util/sound.h"
#include "../../util/soundfx.h"

class MainMenuScreen: public Screen
{
    private:
        std::vector<MenuEntry *> m_menuEntries;
        Texture2D *m_mainMenuTexture;
        SpriteFont *m_font;
        char buffer [64];
        Sound *m_music;
        SoundFX *m_itemMenuFX;
        SoundFX *m_selectItemMenuFX;
        Vector2 m_menuPosition;
        float m_menuInterval;
        int m_selectedEntry;

        //Input
        bool *m_keyStates;
        std::vector<bool> m_oldKeyStates;

    public:
        MainMenuScreen(unsigned int windowW, unsigned int windowH, SpriteFont *font, Sound *music, bool *keyStates): Screen(windowW, windowH)
        {
            m_font = font;
            m_music = music;
            m_keyStates = keyStates;
            m_menuPosition = Vector2(m_windowW/2, 130);
            m_menuInterval = 40.0f;

            m_oldKeyStates.resize(256);
        }

        virtual ~MainMenuScreen();

        void initialize();
        void update(float gameTime);
        void draw();
        void load();
        void unload();

        void upMenu();
        void downMenu();
        void selectMenu();
};

#endif // __MAINMENU_SCREEN_H__
