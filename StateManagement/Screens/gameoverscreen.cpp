#include "gameoverscreen.h"

GameOverScreen::~GameOverScreen()
{
    //dtor
}

void
GameOverScreen::initialize()
{
    m_music->play();
    m_alphaTransition = 1.0f;

    char buffer[32];
    sprintf(buffer, "%d", m_game->getScore());

    //m_scoreMenu = new MenuEntry(std::string(itoa(m_game->getScore(),buffer,10)));
    m_scoreMenu = new MenuEntry(std::string(buffer));
    m_scoreMenu->select();

    if (m_initialized)
        return;

    load();

    m_initialized = true;
}

void
GameOverScreen::update(float gameTime)
{
    m_music->update();

    m_scoreMenu->update(gameTime);

    switch (m_screenState)
    {
        case ScreenState::FadeIn:

                if (m_alphaTransition > 0.0f)
                {
                     m_alphaTransition -= 0.02f;
                }

                if (m_alphaTransition <= 0.0f)
                {
                    m_alphaTransition = 0.0f;
                    m_screenState = ScreenState::Active;
                }

        case ScreenState::Active:

                if (m_keyStates[Keys::Space] && !m_oldKeyStates[Keys::Space])
                {
                    m_nextScreen = 0;
                    m_screenState = ScreenState::FadeOut;
                }

                break;

        case ScreenState::FadeOut:

                if (m_alphaTransition < 1.0f)
                {
                     m_alphaTransition += 0.02f;
                }

                if (m_alphaTransition >= 1.0f)
                {
                    m_alphaTransition = 1.0f;
                    m_music->pause();
                    m_screenState = ScreenState::Hidden;
                }

                break;
    }

    std::copy(m_keyStates, m_keyStates+256, m_oldKeyStates.begin());
}

void
GameOverScreen::draw()
{
    m_gameOverTexture->draw();

    SpriteBatch::DrawStringCentralizedXY(m_font, 1.0f, "Final Score:", Vector2(m_windowW/2, 200), Color3d(255,255,255));
    m_scoreMenu->draw(m_font, Vector2(m_windowW/2, 150), Color3d(255,215,0));

    drawFading(m_alphaTransition);
}

void
GameOverScreen::load()
{
    m_gameOverTexture = new Texture2D("Content/endMenu.png");
}

void
GameOverScreen::unload()
{
    std::cout << "unload game over\n";

    if (m_initialized == false)
        return;

    m_gameOverTexture->~Texture2D();
    m_font->~SpriteFont();

    std::vector<bool>().swap(m_oldKeyStates);
}
