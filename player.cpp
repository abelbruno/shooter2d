#include "player.h"

Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void
Player::initialize(Animation *animation, Vector2 pos)
{
    m_playerAnimation = animation;
    m_position = pos;
    m_active = true;
    m_health = 100;
}

void
Player::update(float gameTime)
{
    m_playerAnimation->setPosition(m_position);
    m_playerAnimation->update(gameTime);
}

void
Player::draw()
{
    m_playerAnimation->draw();
}

void
Player::setPos(Vector2 pos)
{
    m_position = pos;
    m_playerAnimation->setPosition(m_position);
}
