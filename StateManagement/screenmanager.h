#ifndef __SCREEN_MANAGER_H__
#define __SCREEN_MANAGER_H__

#include <iostream>
#include <vector>

#include "../util/shaders_util.h"
#include "../util/spritefont.h"
#include "../util/sound.h"

#include "Screens/screen.h"
#include "Screens/mainmenuscreen.h"
#include "Screens/loadingscreen.h"
#include "Screens/gamescreen.h"
#include "Screens/gameoverscreen.h"
#include "../game.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ScreenManager
{
    private:
        std::vector<Screen*> m_screens;
        int m_activeScreen;
        SpriteFont* m_font;
        Sound *m_menuMusic;

        const char *vertShaderPath = "shaders/fading.vert";
        const char *fragShaderPath = "shaders/fading.frag";
        GLuint m_fadingProgram;

    public:
        ScreenManager();
        virtual ~ScreenManager();

        void initialize(unsigned int windowW, unsigned int windowH, bool *keyStates, GLFWwindow *context);
        void load();
        void unload();
        void update(float gameTime);
        void draw();

        void addScreen(Screen *screen);
};

#endif // __SCREEN_MANAGER_H__
