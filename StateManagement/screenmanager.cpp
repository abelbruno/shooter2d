#include "screenmanager.h"

GLuint Screen::m_fadingProgram;

ScreenManager::ScreenManager()
{
    //ctor
}

ScreenManager::~ScreenManager()
{
    //dtor
}

void
ScreenManager::initialize(unsigned int windowW, unsigned int windowH, bool *keyStates, GLFWwindow *context)
{
    m_fadingProgram = loadGLSLProgram(vertShaderPath, 0, fragShaderPath);
    m_font = new SpriteFont("Content/pixel_classic.ttf");
    m_menuMusic = new Sound("Content/Sound/menuMusic.ogg", true);

    //==============================================
    //Init the Fading Program for all derived classes from Screen
    Screen::m_fadingProgram = m_fadingProgram;

    m_screens.push_back(new MainMenuScreen(windowW, windowH, m_font, m_menuMusic, keyStates));
    GameScreen *gameScreen = new GameScreen(windowW, windowH, context, keyStates);
    m_screens.push_back(new LoadingScreen(windowW, windowH, gameScreen, m_menuMusic));
    m_screens.push_back(gameScreen);
    m_screens.push_back(new GameOverScreen(windowW, windowH, gameScreen->getGame(), m_menuMusic, keyStates));

    m_activeScreen = 0;

    m_screens[m_activeScreen]->setState(ScreenState::FadeIn);
    m_screens[m_activeScreen]->initialize();
}

void
ScreenManager::update(float gameTime)
{
    m_screens[m_activeScreen]->update(gameTime);

    if (m_screens[m_activeScreen]->getState() == ScreenState::Hidden)
    {
        m_activeScreen = m_screens[m_activeScreen]->getNext();

        //Exit Application
        if (m_activeScreen < 0)
        {
            glfwSetWindowShouldClose(glfwGetCurrentContext(), GL_TRUE);
            return;
        }

        m_screens[m_activeScreen]->setState(ScreenState::FadeIn);

        m_screens[m_activeScreen]->initialize();
    }
}

void
ScreenManager::draw()
{
    for (int i = 0; i < m_screens.size(); i++)
    {
        if (m_screens[i]->isHidden() == false)
            m_screens[i]->draw();
    }
}

void
ScreenManager::unload()
{
    m_font->~SpriteFont();
    m_menuMusic->~Sound();

    for (int i = m_screens.size()-1; i >= 0; i--)
    {
        m_screens[i]->unload();
    }
}

void
ScreenManager::addScreen(Screen *screen)
{
    m_screens.push_back(screen);
}
