#ifndef __SOUNDFX_H__
#define __SOUNDFX_H__

#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

class SoundFX
{
    private:
        std::string m_fileName;
        ALuint buffer;
        ALuint source;

        void load();

    public:
        SoundFX(const std::string& fileName);
        virtual ~SoundFX();

        void play();
        void pause();
        void stop();

        bool isPlaying();
        bool isPaused();
        bool isStopped();
};

#endif // __SOUNDFX_H__
