#include "projectile.h"

Projectile::Projectile()
{
    //ctor
}

Projectile::~Projectile()
{
    //dtor
}

void
Projectile::initialize(Rect viewport, Texture2D *texture, Vector2 position)
{
    m_texture  = texture;
    m_position = position;
    m_viewport = viewport;

    m_active = true;

    m_damage = 2;
    m_projectileMoveSpeed = 20.0f;
}

void
Projectile::update(float gameTime)
{
    m_position.x += m_projectileMoveSpeed;

    if (m_position.x + getWidth() / 2 > m_viewport.width)
    {
        m_active = false;
    }
}

void
Projectile::draw()
{
    if (m_active)
        m_texture->draw(m_position);
}
