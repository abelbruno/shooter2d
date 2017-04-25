#include "sound.h"

Sound::Sound(const std::string& fileName, bool looping)
{
    m_fileName = fileName;
    m_ogg      = new OggStream();
    m_looping  = looping;

    load();
}

Sound::~Sound()
{
    m_ogg->release();
}

void
Sound::load()
{
    try
    {
        m_ogg->open(m_fileName, m_looping);

        m_ogg->display();
    }
    catch(std::string error)
    {
        std::cout << error;
    }
}

void
Sound::play()
{
    if (m_ogg->isStopped())
        m_ogg->playback();

    m_ogg->play();
}

void
Sound::pause()
{
    if (m_ogg->isPlaying())
        m_ogg->pause();
}

void
Sound::stop()
{
    if (m_ogg->isPlaying())
        m_ogg->stop();
}

void
Sound::update()
{
    if (m_ogg->isPlaying())
        m_ogg->update();
}
