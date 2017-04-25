#include "enemy.h"

Enemy::Enemy()
{
    //ctor
}

Enemy::~Enemy()
{
    //dtor
}

void
Enemy::initialize(Animation *animation, Vector2 position)
{
    m_enemyAnimation = animation;
    m_position = position;

    m_active = true;

    m_health = 10;
    m_damage = 25;
    m_enemyMoveSpeed = 6.0f;

    m_value = 100;
}

void
Enemy::update(float gameTime)
{
    m_position.x -= m_enemyMoveSpeed;

    m_enemyAnimation->setPosition(m_position);
    m_enemyAnimation->update(gameTime);

    if (m_position.x < -getWidth() || m_health <= 0)
    {
        m_active = false;
    }
}

void
Enemy::draw()
{
    if (m_active)
    {
        m_enemyAnimation->draw();
    }
}
