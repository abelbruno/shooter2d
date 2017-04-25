#include "oggstream.h"

OggStream::OggStream()
{
    //ctor
}

OggStream::~OggStream()
{
    //dtor
}

void
OggStream::open(string path, bool looping)
{
    int result;

    if(!(oggFile = fopen(path.c_str(), "rb")))
        throw string("Could not open Ogg file.");

    if((result = ov_open(oggFile, &oggStream, NULL, 0)) < 0)
    {
        fclose(oggFile);

        throw string("Could not open Ogg stream. ") + errorString(result);
    }

    vorbisInfo = ov_info(&oggStream, -1);
    vorbisComment = ov_comment(&oggStream, -1);

    if(vorbisInfo->channels == 1)
        format = AL_FORMAT_MONO16;
    else
        format = AL_FORMAT_STEREO16;

    alGenBuffers(2, buffers);
    check();
    alGenSources(1, &source);
    check();

    alSource3f(source, AL_POSITION,        0.0, 0.0, 0.0);
    alSource3f(source, AL_VELOCITY,        0.0, 0.0, 0.0);
    alSource3f(source, AL_DIRECTION,       0.0, 0.0, 0.0);
    alSourcef (source, AL_ROLLOFF_FACTOR,  0.0          );
    alSourcei (source, AL_SOURCE_RELATIVE, AL_TRUE      );
    alSourcei (source, AL_LOOPING, AL_FALSE);

    m_looping = looping;
}

void
OggStream::play()
{
    alSourcePlay(source);
}

void
OggStream::pause()
{
    alSourcePause(source);
}

void
OggStream::stop()
{
    alSourceStop(source);
}

void
OggStream::release()
{
    alSourceStop(source);
    empty();
    alDeleteSources(1, &source);
    check();
    alDeleteBuffers(1, buffers);
    check();

    ov_clear(&oggStream);
}

void
OggStream::display()
{
    cout
        << "version         " << vorbisInfo->version         << "\n"
        << "channels        " << vorbisInfo->channels        << "\n"
        << "rate (hz)       " << vorbisInfo->rate            << "\n"
        << "bitrate upper   " << vorbisInfo->bitrate_upper   << "\n"
        << "bitrate nominal " << vorbisInfo->bitrate_nominal << "\n"
        << "bitrate lower   " << vorbisInfo->bitrate_lower   << "\n"
        << "bitrate window  " << vorbisInfo->bitrate_window  << "\n"
        << "\n"
        << "vendor " << vorbisComment->vendor << "\n";

    for(int i = 0; i < vorbisComment->comments; i++)
        cout << "   " << vorbisComment->user_comments[i] << "\n";

    cout << endl;
}

bool
OggStream::playback()
{
    if(isPlaying())
        return true;

    if(!stream(buffers[0]))
        return false;

    if(!stream(buffers[1]))
        return false;

    alSourceQueueBuffers(source, 2, buffers);

    return true;
}

bool
OggStream::isPlaying()
{
    ALenum state;

    alGetSourcei(source, AL_SOURCE_STATE, &state);

    return (state == AL_PLAYING);
}

bool
OggStream::isPaused()
{
    ALenum state;

    alGetSourcei(source, AL_SOURCE_STATE, &state);

    return (state == AL_PAUSED);
}

bool
OggStream::isStopped()
{
    ALenum state;

    alGetSourcei(source, AL_SOURCE_STATE, &state);

    return (state == AL_STOPPED || state == AL_INITIAL);
}

void
OggStream::getState()
{
    ALenum state;

    alGetSourcei(source, AL_SOURCE_STATE, &state);

    if (state == AL_PLAYING) cout << "state: Playing!\n";
    else if (state == AL_PAUSED)  cout << "state: Paused!\n";
    else if (state == AL_STOPPED) cout << "state: Stopped!\n";
    else if (state == AL_INITIAL) cout << "state: Initial!\n";
    else cout << "state error: " << state << "\n";
}

bool
OggStream::update()
{

    if (!isPlaying())
        return false;

    int processed;
    bool active = true;

    alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);

    while(processed--)
    {
        ALuint buffer;

        alSourceUnqueueBuffers(source, 1, &buffer);
        check();

        active = stream(buffer);

        if (active)
        {
            alSourceQueueBuffers(source, 1, &buffer);
            check();
        }
    }

    if (!active)
    {
        setStreamPos(0.0f);
        alSourceStop(source);
        empty();

        if (m_looping)
        {
            active = true;
            playback();
            play();
        }
    }

    return active;
}

bool
OggStream::stream(ALuint buffer)
{
    char data[BUFFER_SIZE];
    int  size = 0;
    int  section;
    int  result;

    while(size < BUFFER_SIZE)
    {
        result = ov_read(&oggStream, data + size, BUFFER_SIZE - size, 0, 2, 1, & section);

        if(result > 0)
            size += result;
        else
            if(result < 0)
                throw errorString(result);
            else
                break;
    }

    if(size == 0)
        return false;

    alBufferData(buffer, format, data, size, vorbisInfo->rate);
    check();

    return true;
}

void
OggStream::setStreamPos(float pos)
{
    ov_time_seek(&oggStream, pos);
}

float
OggStream::getStreamPos()
{
    return (float)ov_time_tell(&oggStream);
}

void
OggStream::empty()
{
    int queued;

    alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);

    while(queued--)
    {
        ALuint buffer;

        alSourceUnqueueBuffers(source, 1, &buffer);
        check();
    }
}

void
OggStream::check()
{
    int error = alGetError();

    if(error != AL_NO_ERROR)
    {
        cout << "Check: " << error << "\n";
        throw string("OpenAL error was raised.");
    }
}

string
OggStream::errorString(int code)
{
    switch(code)
    {
        case OV_EREAD:
            return string("Read from media.");
        case OV_ENOTVORBIS:
            return string("Not Vorbis data.");
        case OV_EVERSION:
            return string("Vorbis version mismatch.");
        case OV_EBADHEADER:
            return string("Invalid Vorbis header.");
        case OV_EFAULT:
            return string("Internal logic fault (bug or heap/stack corruption.");
        default:
            return string("Unknown Ogg error.");
    }
}
