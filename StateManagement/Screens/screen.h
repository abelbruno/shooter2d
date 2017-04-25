#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <GL/glew.h>

enum class ScreenState
{
    FadeIn,
    FadeOut,
    Active,
    Paused,
    Hidden,
    Ready
};

class Screen
{
    protected:
        ScreenState m_screenState;
        float m_transitionOnTime;
        float m_transitionOffTime;
        float m_alphaTransition;
        unsigned int m_windowW;
        unsigned int m_windowH;
        bool m_initialized;
        int m_nextScreen;

    public:
        static GLuint m_fadingProgram;

        Screen(unsigned int windowW, unsigned int windowH);
        virtual ~Screen();

        virtual void initialize() = 0;
        virtual void update(float gameTime) = 0;
        virtual void draw() = 0;
        virtual void load() = 0;
        virtual void unload() = 0;

        virtual void drawFading(float alpha);
        virtual bool isActive() {return (m_screenState == ScreenState::Active);}
        virtual bool isPaused() {return (m_screenState == ScreenState::Paused);}
        virtual bool isHidden() {return (m_screenState == ScreenState::Hidden);}
        virtual bool isInitialized() {return m_initialized;}
        virtual float getTransitionOnTime() {return m_transitionOnTime;}
        virtual float getTransitionOffTime() {return m_transitionOffTime;}
        virtual int getNext() {return m_nextScreen;}
        virtual ScreenState  getState() {return m_screenState;}
        virtual void setState(ScreenState state) {m_screenState = state;}
};

#endif // __SCREEN_H__
