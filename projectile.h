#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "util/game_util.h"
#include "util/texture2d.h"

class Projectile
{
    private:
        Texture2D *m_texture;
        Vector2 m_position;
        Rect m_viewport;
        bool m_active;
        int m_damage;
        float m_projectileMoveSpeed;

    public:
        Projectile();
        virtual ~Projectile();

        void initialize(Rect viewport, Texture2D *texture, Vector2 position);
        void update(float gameTime);
        void draw();

        bool isActive() {return m_active;}
        float getX() {return m_position.x;}
        float getY() {return m_position.y;}
        Vector2 getPos() {return m_position;}
        int getWidth() {return m_texture->getWidth();}
        int getHeight() {return m_texture->getHeight();}
        int getDamage() {return m_damage;}
        void setActive(bool active) {m_active = active;}
};

#endif // __PROJECTILE_H__
