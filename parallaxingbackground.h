#ifndef __PARALLAXING_BACKGROUND_H__
#define __PARALLAXING_BACKGROUND_H__

#include <vector>
#include <string>
#include "util/game_util.h"
#include "util/texture2d.h"

#include <iostream>

class ParallaxingBackground
{
    private:
        Texture2D *m_texture;
        Vector2 *m_positions;
        int m_positionsCount;
        int m_speed;

    public:
        ParallaxingBackground();
        virtual ~ParallaxingBackground();

        void initialize(std::string texturePath, int screenWidth, int speed);
        void update();
        void draw();
};

#endif // __PARALLAXING_BACKGROUND_H__
