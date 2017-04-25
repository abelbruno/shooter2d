#ifndef __GAMEOVER_SCREEN_H__
#define __GAMEOVER_SCREEN_H__

#include <cstdio>   //sprintf()
#include <cstdlib>
#include <string>

#include "screen.h"
#include "menuentry.h"
#include "../../game.h"
#include "../../util/game_util.h"
#include "../../util/texture2d.h"
#include "../../util/spritefont.h"
#include "../../util/spritebatch.h"
#include "../../util/sound.h"

class GameOverScreen : public Screen
{
    private:
        Game *m_game;
        Texture2D *m_gameOverTexture;
        MenuEntry *m_scoreMenu;
        SpriteFont *m_font;
        Sound *m_music;

        //Input
        bool *m_keyStates;
        std::vector<bool> m_oldKeyStates;

    public:
        GameOverScreen(unsigned int windowW, unsigned int windowH, Game* game, Sound *music, bool *keyStates): Screen(windowW, windowH)
        {
            m_font = new SpriteFont("Content/pixel_classic.ttf");
            m_game = game;
            m_music = music;
            m_keyStates = keyStates;

            m_oldKeyStates.resize(256);
        }

        virtual ~GameOverScreen();

        void initialize();
        void update(float gameTime);
        void draw();
        void load();
        void unload();
};

#endif // __GAMEOVER_SCREEN_H__
