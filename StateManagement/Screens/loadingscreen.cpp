#include "loadingscreen.h"

LoadingScreen::~LoadingScreen()
{
    //dtor
}

void
LoadingScreen::initialize()
{
    m_pNextScreen->initialize();

    if (m_initialized)
        return;

    load();

    m_initialized = true;
}

void
LoadingScreen::update(float gameTime)
{
    if (m_screenState != ScreenState::Active)
        m_screenState = ScreenState::Active;

    m_loadingAnimation->update(gameTime);

    m_music->update();

    if (m_pNextScreen->getState() == ScreenState::Ready)
    {
        m_music->pause();
        m_nextScreen = 2;
        m_screenState = ScreenState::Hidden;
    }
}

void
LoadingScreen::draw()
{
    m_loadingAnimation->draw();
}

void
LoadingScreen::load()
{
    m_loadingAnimation = new Animation();
    m_loadingAnimation->initialize(new Texture2D("Content/preloader.png"), Vector2(0,0), 198, 125, 6, 60, 1.0f, true);

    Vector2 position(m_windowW/2 - m_loadingAnimation->getFrameWidth()/2, m_windowH/2 - m_loadingAnimation->getFrameHeight()/2);
    m_loadingAnimation->setPosition(position);
}

void
LoadingScreen::unload()
{
    std::cout << "unload Looping\n";

    if (m_initialized)
        m_loadingAnimation->~Animation();
}
