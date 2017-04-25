#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "util/game_util.h"
#include "util/texture2d.h"
#include "util/animation.h"


class Player
{
    private:
        Animation *m_playerAnimation;
        Vector2 m_position;
        bool m_active;
        int m_health;

    public:
        Player();
        virtual ~Player();

        void initialize(Animation* animation, Vector2 position);
        void update(float gameTime);
        void draw();

        void hit(int damage) {m_health -= damage;}

        bool isAlive() {return (m_health > 0);}
        int getHealth() {return m_health;}
        int getWidth() {return m_playerAnimation->getFrameWidth();}
        int getHeight() {return m_playerAnimation->getFrameHeight();}
        void moveX(float x) {m_position.x += x;}
        void moveY(float y) {m_position.y += y;}
        float getX() {return m_position.x;}
        float getY() {return m_position.y;}
        Vector2 getPos() {return m_position;}
        void setPos(Vector2 pos);
        void setX(float x) {m_position.x = x;}
        void setY(float y) {m_position.y = y;}
        void setActive(bool active) {m_active = active;}
        void setHealth(int health) {m_health = health;}
};

#endif // __PLAYER_H__
