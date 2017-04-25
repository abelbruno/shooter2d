#ifndef __GAME_H__
#define __GAME_H__

#include <ctime>
#include <vector>
#include <string>
#include <cstdio>    //sprintf()
#include <cstdlib>
#include <iostream>
#include <GL/glew.h>
#include <AL/al.h>
#include <AL/alut.h>

#include "util/shaders_util.h"
#include "util/game_util.h"
#include "util/spritebatch.h"
#include "util/sound.h"
#include "util/soundfx.h"
#include "util/spritefont.h"
#include "util/texture2d.h"
#include "util/animation.h"
#include "parallaxingbackground.h"
#include "enemy.h"
#include "player.h"
#include "projectile.h"

class Game
{
    private:

        /***********************************************
        * VARIABLES
        ************************************************/

        //Window
        unsigned int m_windowW;
        unsigned int m_windowH;

        //Game state
        bool m_contentLoaded;

        //Game
        Player *m_player;
        Texture2D *m_playerTexture;
        float m_playerMoveSpeed;
        int m_score;
        Texture2D *m_mainBackground;
        ParallaxingBackground *m_bgLayer1;
        ParallaxingBackground *m_bgLayer2;
        Texture2D *m_enemyTexture;
        std::vector<Enemy> m_enemies;
        float m_enemySpawnTime;
        float m_previousSpawnTime;
        Texture2D *m_projectileTexture;
        std::vector<Projectile> m_projectiles;
        float m_fireTime;
        float m_previousFireTime;
        Texture2D *m_explosionTexture;
        std::vector<Animation> m_explosions;
        SoundFX *m_explosionSound;
        SoundFX *m_laserSound;
        Sound *m_gameplayMusic;
        SpriteFont *m_font;

        //Input
        bool *m_keyStates;

        //Shaders
        GLuint m_texture2DProgram;

        /***********************************************
        * FUNCTIONS
        ************************************************/

        //Player
        void updatePlayer(float gameTime);

        //Enemies
        void updateEnemy(float gameTime);
        void addEnemy();

        //Projectiles
        void updateProjectile(float gameTime);
        void addProjectile(Vector2 position);

        //Explosions
        void updateExplosion(float gameTime);
        void addExplosion(Vector2 position);

        //Collision Detection
        void updateCollision();

    public:
        Game(unsigned int windowW, unsigned int windowH, bool *keyStates);
        virtual ~Game();

        //Main Funcitons
        void initialize();
        void loadContent();
        void unloadContent();
        void update(float gameTime);
        void draw();

        void playGame();
        void pauseGame();
        void quitGame();
        void resetGame();

        int getScore() {return m_score;}
        bool isContentLoaded() {return m_contentLoaded;}
        bool isGameOver() {return !m_player->isAlive();}
};

#endif // __GAME_H__
