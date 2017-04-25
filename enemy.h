#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "util/game_util.h"
#include "util/animation.h"

class Enemy
{
    private:
        Animation *m_enemyAnimation;
        Vector2 m_position;
        bool m_active;
        int m_health;
        int m_damage;
        int m_value;
        float m_enemyMoveSpeed;

    public:
        Enemy();
        virtual ~Enemy();

        void initialize(Animation *animation, Vector2 position);
        void update(float gameTime);
        void draw();

        void hit(int damage) {m_health -= damage;}

        bool isActive() {return m_active;}
        float getX() {return m_position.x;}
        float getY() {return m_position.y;}
        Vector2 getPos() {return m_position;}
        int getWidth() {return m_enemyAnimation->getFrameWidth();}
        int getHeight() {return m_enemyAnimation->getFrameHeight();}
        int getDamage() {return m_damage;}
        int getValue() {return m_value;}
        int getHealth() {return m_health;}
        void setHealth(int health) {m_health = health;}
};

#endif // __ENEMY_H__
