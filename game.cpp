#include "game.h"

Game::Game(unsigned int windowW, unsigned int windowH, bool *keyStates)
{
    m_windowW     = windowW;
    m_windowH     = windowH;
    m_keyStates   = keyStates;
}

Game::~Game()
{
    //dtor
}

/************************************************
 MAIN FUNCTIONS
************************************************/

void
Game::initialize()
{
    m_contentLoaded = false;

    m_player = new Player();
    m_playerMoveSpeed = 4.0f;
    m_score = 0;

    m_bgLayer1 = new ParallaxingBackground();
    m_bgLayer2 = new ParallaxingBackground();

    //Enemies
    m_previousSpawnTime = 0;
    m_enemySpawnTime = 800;

    //Projectiles
    m_previousFireTime = 0;
    m_fireTime = 200;

    std::cout << "\nGAME Initialized: " << m_playerMoveSpeed << "\n\n";
}

void
Game::loadContent()
{
    m_playerTexture = new Texture2D("Content/shipAnimation.png");

    Animation *playerAnimation = new Animation();
    playerAnimation->initialize(m_playerTexture, Vector2(0,0), 115, 69, 8, 60, 1.0f, true);

    m_player->initialize(playerAnimation, Vector2(0, m_windowH/2));

    m_bgLayer1->initialize("Content/bgLayer1.png", m_windowW, -1);
    m_bgLayer2->initialize("Content/bgLayer2.png", m_windowW, -2);

    m_mainBackground = new Texture2D("Content/mainbackground.png");

    m_enemyTexture = new Texture2D("Content/mineAnimation.png");

    m_projectileTexture = new Texture2D("Content/laser.png");

    m_explosionTexture  = new Texture2D("Content/explosion.png");

    //Game Sounds
    m_explosionSound = new SoundFX("Content/Sound/explosion.wav");
    m_laserSound = new SoundFX("Content/Sound/laserFire.wav");
    m_gameplayMusic = new Sound("Content/Sound/gameMusic.ogg", 1);

    //Game Font
    //font = new SpriteFont("Content/impact.ttf");
    m_font = new SpriteFont("Content/pixel_classic.ttf");

    m_contentLoaded = true;
}

void
Game::unloadContent()
{
    m_playerTexture->~Texture2D();
    m_bgLayer1->~ParallaxingBackground();
    m_bgLayer2->~ParallaxingBackground();
    m_mainBackground->~Texture2D();
    m_enemyTexture->~Texture2D();
    m_projectileTexture->~Texture2D();
    m_explosionTexture->~Texture2D();
    m_font->~SpriteFont();

//========================================
// BUG:
// Sound must be the first sound destructed
// else "alSourceUnqueueBuffers" in empty() [oggstream.cpp]
// throw an error.
//========================================

    m_gameplayMusic->~Sound();
    m_laserSound->~SoundFX();
    m_explosionSound->stop();
    m_explosionSound->~SoundFX();

    std::cout << "Game Unloaded!!\n";
}

void
Game::update(float gameTime)
{
    if (m_player->isAlive())
        updatePlayer(gameTime);

    m_bgLayer1->update();
    m_bgLayer2->update();

    updateEnemy(gameTime);

    updateProjectile(gameTime);

    updateExplosion(gameTime);

    updateCollision();

    m_gameplayMusic->update();
}

void
Game::updatePlayer(float gameTime)
{
    m_player->update(gameTime);

    if (m_keyStates[Keys::A])
        m_player->moveX(-1 * m_playerMoveSpeed);

    if (m_keyStates[Keys::D])
        m_player->moveX(m_playerMoveSpeed);

    if (m_keyStates[Keys::S])
        m_player->moveY(-1 * m_playerMoveSpeed);

    if (m_keyStates[Keys::W])
        m_player->moveY(m_playerMoveSpeed);

    m_player->setX(std::max(0.0f, std::min(m_player->getX(), (float)m_windowW - m_player->getWidth())));
    m_player->setY(std::max(0.0f, std::min(m_player->getY(), (float)m_windowH - m_player->getHeight())));

    if (gameTime - m_previousFireTime > m_fireTime)
    {
        m_previousFireTime = gameTime;

        addProjectile(m_player->getPos() + Vector2(m_player->getWidth()/2, 20));

        m_laserSound->play();
    }
}

void
Game::updateEnemy(float gameTime)
{
    if (gameTime - m_previousSpawnTime > m_enemySpawnTime)
    {
        m_previousSpawnTime = gameTime;

        //Add an Enemy
        addEnemy();
    }

    //Update enemies
    for (int i = m_enemies.size() - 1; i >= 0; i--)
    {
        m_enemies[i].update(gameTime);

        if (m_enemies[i].isActive() == false)
        {
            if (m_enemies[i].getHealth() <= 0)
            {
                //Centralize the explosion animation
                addExplosion(m_enemies[i].getPos() - Vector2(44, 36));
                m_explosionSound->play();

                m_score += m_enemies[i].getValue();
            }

            m_enemies.erase(m_enemies.begin()+i);
        }
    }
}

void
Game::updateProjectile(float gameTime)
{
    for (int i = m_projectiles.size() - 1; i >= 0; i--)
    {
        m_projectiles[i].update(gameTime);

        if (m_projectiles[i].isActive() == false)
        {
            m_projectiles.erase(m_projectiles.begin() + i);
        }
    }
}

void
Game::updateExplosion(float gameTime)
{
    for (int i = m_explosions.size() - 1; i >= 0; i--)
    {
        m_explosions[i].update(gameTime);

        if (m_explosions[i].isActive() == false)
        {
            m_explosions.erase(m_explosions.begin() + i);
        }
    }
}

void
Game::updateCollision()
{
    Rect rectangle1;
    Rect rectangle2;

    rectangle1 = Rect((int)m_player->getX(), (int)m_player->getY(), m_player->getWidth(), m_player->getHeight() );

    if (m_player->isAlive())
    {
        for (int i = 0; i < m_enemies.size(); i++)
        {
            rectangle2 = Rect((int)m_enemies[i].getX(), (int)m_enemies[i].getY(), m_enemies[i].getWidth(), m_enemies[i].getHeight());

            if (rectangle1.intersects(rectangle2))
            {
                m_player->hit(m_enemies[i].getDamage());

                m_enemies[i].setHealth(0);

                if (m_player->isAlive() == false)
                {
                    //Centralize the explosion animation
                    addExplosion(m_player->getPos() - Vector2(0, 36));
                    m_explosionSound->play();
                }
            }
        }
    }

    for (int i = 0; i < m_projectiles.size(); i++)
    {
        rectangle1 = Rect((int)m_projectiles[i].getX(), (int)m_projectiles[i].getY(),
                           m_projectiles[i].getWidth(), m_projectiles[i].getHeight());

        for (int j = 0; j < m_enemies.size(); j++)
        {
            rectangle2 = Rect((int)m_enemies[j].getX(), (int)m_enemies[j].getY(),
                               m_enemies[j].getWidth(), m_enemies[j].getHeight());

            if (rectangle1.intersects(rectangle2))
            {
                m_enemies[j].hit(m_projectiles[i].getDamage());
                m_projectiles[i].setActive(false);
            }
        }
    }
}

void
Game::addEnemy()
{
    Animation *enemyAnimation = new Animation();
    enemyAnimation->initialize(m_enemyTexture, Vector2(0,0), 47, 61, 8, 60, 1.0f, true);

    Vector2 position(m_windowW + m_enemyTexture->getWidth()/2, rand() % (m_windowH - enemyAnimation->getFrameHeight()) + 10);

    Enemy enemy;
    enemy.initialize(enemyAnimation, position);

    m_enemies.push_back(enemy);
}

void
Game::addProjectile(Vector2 position)
{
    Projectile projectile;
    projectile.initialize(Rect(0, 0, m_windowW, m_windowH), m_projectileTexture, position);

    m_projectiles.push_back(projectile);
}

void
Game::addExplosion(Vector2 position)
{
    Animation explosion;
    explosion.initialize(m_explosionTexture,position, 134, 134, 12, 70, 1.0f,false);

    m_explosions.push_back(explosion);
}

void
Game::draw()
{
    m_mainBackground->draw();

    m_bgLayer1->draw();
    m_bgLayer2->draw();

    if (m_player->isAlive())
        m_player->draw();

    for (int i = 0; i < m_enemies.size(); i++)
    {
        m_enemies[i].draw();
    }

    for (int i = 0; i < m_projectiles.size(); i++)
    {
        m_projectiles[i].draw();
    }

    for (int i = 0; i < m_explosions.size(); i++)
    {
        m_explosions[i].draw();
    }

    char buffer [32];
    sprintf(buffer, "%d", m_score);

    //SpriteBatch::DrawString(m_font, std::string("Score: ") + std::string(itoa(m_score,buffer,10)),
    SpriteBatch::DrawString(m_font, std::string("Score: ") + std::string(buffer),
                           Vector2(10, m_windowH - 30), Color3d(255,255,255));

    sprintf(buffer, "%d", m_player->getHealth());
    //SpriteBatch::DrawString(m_font, std::string("Health: ") + std::string(itoa(m_player->getHealth(),buffer,10)),
    SpriteBatch::DrawString(m_font, std::string("Health: ") + std::string(buffer),
                           Vector2(10, m_windowH - 55), Color3d(255,255,255));

}

void
Game::playGame()
{
    m_gameplayMusic->play();

    if (m_explosionSound->isPaused())
        m_explosionSound->play();

    if (m_laserSound->isPaused())
        m_laserSound->play();
}

void
Game::pauseGame()
{
    m_gameplayMusic->pause();

    if (m_explosionSound->isPlaying())
        m_explosionSound->pause();

    if (m_laserSound->isPlaying())
        m_laserSound->pause();
}

void
Game::quitGame()
{
    pauseGame();

    m_gameplayMusic->stop();
    m_explosionSound->stop();
    m_laserSound->stop();

    //resetGame();
}

void
Game::resetGame()
{
    m_score = 0;

    m_player->setPos(Vector2(0, m_windowH/2));
    m_player->setHealth(100);

    m_enemies.clear();
    m_explosions.clear();
    m_projectiles.clear();

    m_previousSpawnTime = 0;
}
