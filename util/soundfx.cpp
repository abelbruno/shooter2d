#include "soundfx.h"

SoundFX::SoundFX(const std::string &fileName)
{
    m_fileName = fileName;
    load();
}

SoundFX::~SoundFX()
{
    alSourceStop(source);

    alDeleteBuffers(1, &buffer);
    alDeleteSources(1, &source);
}

void
SoundFX::load()
{
    buffer = alutCreateBufferFromFile(m_fileName.c_str());

    alGenSources(1, &source);

    if (alGetError() != AL_NO_ERROR)
        std::cout << "Error loading SFX " << m_fileName << ": " << alGetError();

    alSourcei (source, AL_BUFFER,   buffer   );
    alSource3f(source, AL_POSITION,        0.0, 0.0, 0.0);
    alSource3f(source, AL_VELOCITY,        0.0, 0.0, 0.0);
    alSource3f(source, AL_DIRECTION,       0.0, 0.0, 0.0);
    alSourcef (source, AL_PITCH,    1.0f     );
    alSourcef (source, AL_GAIN,     1.0f     );
    alSourcei (source, AL_LOOPING, AL_FALSE);
    //alSourcei (Source, AL_LOOPING,  AL_TRUE  );
}

void
SoundFX::play()
{
    alSourcePlay(source);
}

void
SoundFX::pause()
{
    alSourcePause(source);
}

void
SoundFX::stop()
{
    alSourceStop(source);
}

bool
SoundFX::isPlaying()
{
    ALenum state;

    alGetSourcei(source, AL_SOURCE_STATE, &state);

    return (state == AL_PLAYING);
}

bool
SoundFX::isPaused()
{
    ALenum state;

    alGetSourcei(source, AL_SOURCE_STATE, &state);

    return (state == AL_PAUSED);
}

bool
SoundFX::isStopped()
{
    ALenum state;

    alGetSourcei(source, AL_SOURCE_STATE, &state);

    return (state == AL_STOPPED || state == AL_INITIAL);
}

