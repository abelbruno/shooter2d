#include "mainmenuscreen.h"

MainMenuScreen::~MainMenuScreen()
{
    //dtor
}

void
MainMenuScreen::initialize()
{
    m_music->play();
    m_alphaTransition = 1.0f;

    if (m_initialized)
        return;

    load();

    m_menuEntries.push_back(new MenuEntry(std::string("PLAY GAME")));
    m_menuEntries.push_back(new MenuEntry(std::string("OPTIONS")));
    m_menuEntries.push_back(new MenuEntry(std::string("EXIT")));

    m_selectedEntry = 0;
    m_menuEntries[m_selectedEntry]->select();

    m_initialized = true;
}

void
MainMenuScreen::update(float gameTime)
{
    m_music->update();

    for (int i = 0; i < m_menuEntries.size(); i++)
        m_menuEntries[i]->update(gameTime);

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

                if (m_keyStates[Keys::Space])
                    selectMenu();

                if (m_keyStates[Keys::W] && !m_oldKeyStates[Keys::W])
                    upMenu();

                if (m_keyStates[Keys::S] && !m_oldKeyStates[Keys::S])
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
MainMenuScreen::draw()
{
    m_mainMenuTexture->draw();

    for (int i = m_menuEntries.size()-1, j = 0; i >= 0; i-- , j++)
    {
        if (i == m_selectedEntry)
            m_menuEntries[i]->draw(m_font, m_menuPosition + Vector2(0, j*m_menuInterval), Color3d(255,215,0));
        else
            m_menuEntries[i]->draw(m_font, m_menuPosition + Vector2(0, j*m_menuInterval), Color3d(255,255,255));
    }

    drawFading(m_alphaTransition);
}

void
MainMenuScreen::load()
{
    m_mainMenuTexture = new Texture2D("Content/mainMenu.png");

    m_itemMenuFX = new SoundFX("Content/Sound/itemMenu.wav");
    m_selectItemMenuFX = new SoundFX("Content/Sound/selectItem.wav");
}

void
MainMenuScreen::unload()
{
    std::cout << "unload mainMenu\n";

    if (m_initialized == false)
        return;

    m_mainMenuTexture->~Texture2D();

    m_itemMenuFX->~SoundFX();
    m_selectItemMenuFX->~SoundFX();

    std::vector<bool>().swap(m_oldKeyStates);
}

void
MainMenuScreen::upMenu()
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
MainMenuScreen::downMenu()
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
MainMenuScreen::selectMenu()
{
    m_selectItemMenuFX->play();

    switch (m_selectedEntry)
    {
        case 0:
        case 1: m_nextScreen = 1;
                break;

        case 2: m_nextScreen = -1;
                break;
    }

    m_screenState = ScreenState::FadeOut;
}
