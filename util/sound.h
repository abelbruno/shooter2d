#ifndef __SOUND_H__
#define __SOUND_H__

#include <string>
#include <iostream>
#include <AL/al.h>
#include <AL/alut.h>

#include "oggstream.h"

class Sound
{
    private:
        std::string m_fileName;
        OggStream *m_ogg;
        float m_duration;
        bool m_looping;

        void load();

    public:
        Sound(const std::string& fileName, bool looping);
        virtual ~Sound();

        void play();
        void pause();
        void stop();
        void update();
        bool isPlaying() {return m_ogg->isPlaying();}
        bool isLooping() {return m_looping;}
        void getState() {m_ogg->getState();}
        void setLooping(bool looping) {m_looping = looping;}
        float getDuration() {return m_duration;}
};

#endif // __SOUND_H__
