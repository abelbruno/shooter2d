#include "animation.h"

Animation::Animation()
{
    //ctor
}

Animation::~Animation()
{
    //ctor
}

void
Animation::initialize(Texture2D *texture, Vector2 position, int frameWidth, int frameHeight,
                        int frameCount, int frameTime, float scale, bool looping)
{
    m_sprite   = texture;
    m_position = position;

    m_frameWidth  = frameWidth;
    m_frameHeight = frameHeight;
    m_frameCount  = frameCount;
    m_frameTime   = frameTime;

    m_scale = scale;
    m_looping = looping;

    //Set the time to zero
    m_elapsedTime  = 0;
    m_oldGameTime  = 0;
    m_currentFrame = 0;

    //Set the Animation to Active by default
    m_active = true;
}

void
Animation::update(float gameTime)
{
    int newGameTime = (int)gameTime;
    m_elapsedTime  += newGameTime - m_oldGameTime;
    m_oldGameTime   = newGameTime;

    if (m_elapsedTime > m_frameTime)
    {
        m_currentFrame++;

        if (m_currentFrame == m_frameCount)
        {
            m_currentFrame = 0;

            if (m_looping == false)
                m_active = false;
        }

        m_elapsedTime = 0;
    }

    m_sourceRect = Rect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);

    m_destRect = Rect(m_position.x, m_position.y, m_frameWidth, m_frameHeight);
}

void
Animation::draw()
{
    m_sprite->draw(m_sourceRect, m_destRect);
}
