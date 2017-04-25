#include "gamescreen.h"

GameScreen::~GameScreen()
{
    //dtor
}

void
GameScreen::initialize()
{
    m_alphaTransition = 1.0f;

    if (m_initialized)
    {
        m_shooterGame->resetGame();
        m_shooterGame->playGame();
        return;
    }

    load();

    m_initialized = true;
}

void
GameScreen::update(float gameTime)
{
    if (m_keyStates[Keys::Space] && !m_oldKeyStates[Keys::Space])
    {
        if (isActive())
        {
            m_screenState = ScreenState::Paused;
            m_shooterGame->pauseGame();
            m_pauseScreen->setState(ScreenState::Active);
            m_pauseScreen->initialize();
        }
    }

    switch (m_screenState)
    {
        case ScreenState::Active:

                m_shooterGame->update(gameTime);

                if (m_shooterGame->isGameOver())
                {
                    m_nextScreen = 3;
                    m_screenState = ScreenState::FadeOut;
                }

                break;

        case ScreenState::Paused:

                m_pauseScreen->update(gameTime);

                if (m_pauseScreen->getState() == ScreenState::Hidden)
                {
                    if (m_pauseScreen->getNext() < 0)
                    {
                        m_shooterGame->quitGame();
                        m_initialized = false;
                        m_screenState = ScreenState::Hidden;
                        m_nextScreen = 0;
                    }
                    else
                    {
                        m_screenState = ScreenState::Active;
                        m_shooterGame->playGame();
                    }
                }

                break;

        case ScreenState::FadeIn:

                m_shooterGame->update(gameTime);

                if (m_alphaTransition > 0.0f)
                {
                     m_alphaTransition -= 0.02f;
                }

                if (m_alphaTransition <= 0.0f)
                {
                    m_alphaTransition = 0.0f;
                    m_screenState = ScreenState::Active;
                }

                break;

        case ScreenState::FadeOut:

                m_shooterGame->update(gameTime);

                if (m_alphaTransition < 1.0f)
                {
                     m_alphaTransition += 0.02f;
                }

                if (m_alphaTransition >= 1.0f)
                {
                    m_alphaTransition = 1.0f;
                    m_shooterGame->quitGame();
                    m_initialized = false;
                    m_screenState = ScreenState::Hidden;
                }

                break;
    }

    std::copy(m_keyStates, m_keyStates+256, m_oldKeyStates.begin());
}

void
GameScreen::draw()
{
    m_shooterGame->draw();

    drawFading(m_alphaTransition);

    if (m_pauseScreen->isHidden() == false)
        m_pauseScreen->draw();
}

void
GameScreen::load()
{
    struct_args *args = (struct_args*) malloc(sizeof(struct_args));

    args->game    = m_shooterGame;
    args->screen  = this;
    args->context = m_context;

    pthread_t thread1;

    pthread_create(&thread1, NULL, loadParallel, (void*)args);
    pthread_detach (thread1);
}

void*
loadParallel(void *arguments)
{
    struct_args *args = (struct_args *)arguments;

    glfwMakeContextCurrent( args->context );

    GLenum res = glewInit();
    if (res != GLEW_OK) {
        std::cout << "Error: " << glewGetErrorString(res) << "\n";
    }

    float oldTime = (float)clock() / (CLOCKS_PER_SEC/1000);

    std::cout << "Loading Game Contents\n";
    if (args->game->isContentLoaded() == false)
        args->game->loadContent();

    float newTime = (float)clock() / (CLOCKS_PER_SEC/1000);

    while (newTime - oldTime < 5000)
    {
        newTime = (float)clock() / (CLOCKS_PER_SEC/1000);
    }

    args->screen->setState(ScreenState::Ready);

    glfwMakeContextCurrent(NULL);
    free(arguments);
    pthread_exit(NULL);
}

void
GameScreen::unload()
{
    std::cout << "unload GAME\n";

    if (m_shooterGame->isContentLoaded())
        m_shooterGame->unloadContent();

    m_pauseScreen->unload();
}
