#ifndef __GAME_SCREEN_H__
#define __GAME_SCREEN_H__

#include <iostream>
#include <pthread.h>
#include <ctime>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "screen.h"
#include "pausescreen.h"
#include "../../game.h"
#include "../../util/spritebatch.h"
#include "../../util/animation.h"

typedef struct s_struct_args
{
    Game* game;
    Screen* screen;
    GLFWwindow* context;
} struct_args;

void* loadParallel(void *threadid);

class GameScreen : public Screen
{
    private:
        Game *m_shooterGame;
        GLFWwindow *m_context;
        PauseScreen *m_pauseScreen;

        //Input
        bool *m_keyStates;
        std::vector<bool> m_oldKeyStates;

    public:
        GameScreen(unsigned int windowW, unsigned int windowH, GLFWwindow* context, bool *keyStates): Screen(windowW, windowH)
        {
            m_context     = context;
            m_keyStates   = keyStates;
            m_screenState = ScreenState::Hidden;

            m_oldKeyStates.resize(256);

            m_pauseScreen = new PauseScreen(m_windowW, m_windowH, keyStates);

            m_shooterGame = new Game(m_windowW, m_windowH, m_keyStates );
            m_shooterGame->initialize();
        }

        virtual ~GameScreen();

        void initialize();
        void update(float gametime);
        void draw();
        void load();
        void unload();

        Game* getGame() {return m_shooterGame;}
};

#endif // __GAME_SCREEN_H__
