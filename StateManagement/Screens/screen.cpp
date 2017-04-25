#include "screen.h"

Screen::Screen(unsigned int windowW, unsigned int windowH)
{
    m_screenState = ScreenState::Hidden;

    m_transitionOnTime  = 500.0f;
    m_transitionOffTime = 500.0f;
    m_alphaTransition   = 0.0f;
    m_windowW = windowW;
    m_windowH = windowH;
    m_initialized = false;
    m_nextScreen = -1;
}

Screen::~Screen()
{
    //dtor
}

void
Screen::drawFading(float alpha)
{
    glUseProgram( Screen::m_fadingProgram );
    glUniform1f(glGetUniformLocation(Screen::m_fadingProgram, "alpha"), alpha);

    glBegin(GL_QUADS);
        glVertex2d(-1, -1);
        glVertex2d( 1, -1);
        glVertex2d( 1,  1);
        glVertex2d( -1, 1);
	glEnd();

	glUseProgram(0);
}
