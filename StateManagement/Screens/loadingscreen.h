#ifndef __LOADING_SCREEN_H__
#define __LOADING_SCREEN_H__

#include <iostream>

#include "screen.h"
#include "../../util/game_util.h"
#include "../../util/texture2d.h"
#include "../../util/animation.h"
#include "../../util/sound.h"

class LoadingScreen : public Screen
{
    private:
        Screen *m_pNextScreen;
        Animation *m_loadingAnimation;
        Sound *m_music;

    public:
        LoadingScreen(unsigned int windowW, unsigned int windowH, Screen *nextScreen, Sound *music): Screen(windowW, windowH)
        {
            m_pNextScreen = nextScreen;
            m_music = music;
        }
        virtual ~LoadingScreen();

        void initialize();
        void update(float gameTime);
        void draw();
        void load();
        void unload();
};

#endif // __LOADING_SCREEN_H__
