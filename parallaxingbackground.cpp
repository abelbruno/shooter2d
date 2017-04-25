#include "parallaxingbackground.h"

ParallaxingBackground::ParallaxingBackground()
{
    //ctor
}

ParallaxingBackground::~ParallaxingBackground()
{
    m_texture->~Texture2D();
}

void
ParallaxingBackground::initialize(std::string texturePath, int screenWidth, int speed)
{
    m_texture = new Texture2D(texturePath);
    m_speed = speed;
    m_positionsCount = screenWidth/m_texture->getWidth() + 1;

    m_positions = new Vector2[m_positionsCount];

    for (int i = 0; i < m_positionsCount; i++)
    {
        m_positions[i] = Vector2(i * m_texture->getWidth(),0);
    }
}

void
ParallaxingBackground::update()
{
    for (int i = 0; i < m_positionsCount; i++)
    {
        m_positions[i].x += m_speed;

        if (m_speed <= 0)
        {
            if (m_positions[i].x <= -m_texture->getWidth())
            {
                m_positions[i].x = m_texture->getWidth() * (m_positionsCount - 1);
            }
        }
        else
        {
            if (m_positions[i].x >= m_texture->getWidth() * (m_positionsCount - 1))
            {
                m_positions[i].x = -m_texture->getWidth();
            }
        }
    }
}

void
ParallaxingBackground::draw()
{
    for (int i = 0; i < m_positionsCount; i++)
    {
        m_texture->draw(m_positions[i]);
    }
}
