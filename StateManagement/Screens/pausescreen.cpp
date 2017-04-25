#include "pausescreen.h"

PauseScreen::~PauseScreen()
{
    //dtor
}

void
PauseScreen::initialize()
{
    m_soundFX->play();
    m_alphaTransition = 0.0f;
    std::fill(m_oldKeyStates.begin(), m_oldKeyStates.begin()+256, true);

    if (m_initialized)
    {
        m_menuEntries[m_selectedEntry]->reset();
        m_selectedEntry = 0;
        m_menuEntries[m_selectedEntry]->select();
        return;
    }

    m_menuEntries.push_back(new MenuEntry(std::string("RESUME"), false));
    m_menuEntries.push_back(new MenuEntry(std::string("EXIT"), false));

    m_selectedEntry = 0;
    m_menuEntries[m_selectedEntry]->select();

    m_initialized = true;
}

void
PauseScreen::update(float gameTime)
{

    for (int i = 0; i < m_menuEntries.size(); i++)
        m_menuEntries[i]->update(gameTime);

    switch (m_screenState)
    {
        case ScreenState::FadeIn:

                m_screenState = ScreenState::Active;

        case ScreenState::Active:

                if (m_keyStates[Keys::Space] && !m_oldKeyStates[Keys::Space])
                {
                    selectMenu();
                    std::cout << "selected\n";
                }

                if (m_keyStates[Keys::A] && !m_oldKeyStates[Keys::A])
                    upMenu();

                if (m_keyStates[Keys::D] && !m_oldKeyStates[Keys::D])
                    downMenu();

                break;

        case ScreenState::FadeOut:

                if (m_alphaTransition < 1.0f)
                {
                     m_alphaTransition += 0.02f;
                }

                if (m_alphaTransition >= 1.0f)
                {
                    m_alphaTransition = 1.0f;
                    m_screenState = ScreenState::Hidden;
                }

                break;
    }

    std::copy(m_keyStates, m_keyStates+256, m_oldKeyStates.begin());
}

void
PauseScreen::draw()
{
    drawFading(0.7f);

    for (int i = 0; i < m_menuEntries.size(); i++)
    {
        if (i == m_selectedEntry)
            m_menuEntries[i]->draw(m_font, m_menuPosition + Vector2(i*m_menuInterval, 0), Color3d(255,215,0));
        else
            m_menuEntries[i]->draw(m_font, m_menuPosition + Vector2(i*m_menuInterval, 0), Color3d(255,255,255));
    }

    drawFading(m_alphaTransition);
}

void
PauseScreen::load()
{
    m_soundFX = new SoundFX("Content/Sound/pauseGame.wav");
    m_itemMenuFX = new SoundFX("Content/Sound/itemMenu.wav");
    m_selectItemMenuFX = new SoundFX("Content/Sound/selectItem.wav");
}

void
PauseScreen::unload()
{
    std::cout << "unload pauseMenu\n";

    if (m_initialized == false)
        return;

    m_soundFX->~SoundFX();
    m_itemMenuFX->~SoundFX();
    m_selectItemMenuFX->~SoundFX();
    m_font->~SpriteFont();
}

void
PauseScreen::upMenu()
{
    if (m_selectedEntry > 0)
    {
        m_menuEntries[m_selectedEntry]->deselect();
        m_selectedEntry--;
        m_menuEntries[m_selectedEntry]->select();
        m_itemMenuFX->play();
    }
}

void
PauseScreen::downMenu()
{
    if (m_selectedEntry < m_menuEntries.size()-1)
    {
        m_menuEntries[m_selectedEntry]->deselect();
        m_selectedEntry++;
        m_menuEntries[m_selectedEntry]->select();
        m_itemMenuFX->play();
    }
}

void
PauseScreen::selectMenu()
{
    m_selectItemMenuFX->play();

    switch (m_selectedEntry)
    {
        case 0: m_nextScreen = 2;
                m_screenState = ScreenState::Hidden;
                break;

        case 1: m_nextScreen = -1;
                m_screenState = ScreenState::FadeOut;
                break;
    }
}

