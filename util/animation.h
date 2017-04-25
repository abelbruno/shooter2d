#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <GL/glew.h>
#include <iostream>

#include "game_util.h"
#include "texture2d.h"

class Animation
{
    private:
        Texture2D *m_sprite;
        float m_scale;
        int m_elapsedTime;
        int m_oldGameTime;
        int m_frameTime;
        int m_frameCount;
        int m_currentFrame;
        Rect m_sourceRect;
        Rect m_destRect;
        int m_frameWidth;
        int m_frameHeight;
        bool m_active;
        bool m_looping;
        Vector2 m_position;

    public:
        Animation();
        virtual ~Animation();

        void initialize(Texture2D *texture, Vector2 position, int frameWidth, int frameHeight,
                        int frameCount, int frameTime, float scale, bool looping);

        void update(float gameTime);
        void draw();

        bool isActive() {return m_active;}
        int getFrameWidth() {return m_frameWidth;}
        int getFrameHeight() {return m_frameHeight;}
        void setPosition(Vector2 position) {m_position = position;}
};

#endif // __ANIMATION_H__
