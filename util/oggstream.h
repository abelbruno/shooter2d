#ifndef __OGGSTREAM_H__
#define __OGGSTREAM_H__

#include <string>
#include <iostream>
using namespace std;

#include <AL/al.h>
#include <ogg/ogg.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>

#define BUFFER_SIZE (4096 * 100)

class OggStream
{
    public:
        OggStream();
        virtual ~OggStream();

        void open(string path, bool looping); // obtain a handle to the file
        void release();         // release the file handle
        void display();         // display some info on the Ogg
        bool playback();        // play the Ogg stream
        bool update();          // update the stream if necessary
        void play();
        void stop();
        void pause();

        bool isPlaying();
        bool isPaused();
        bool isStopped();
        void getState();
        void setLooping(bool looping) {m_looping = looping;}

    protected:

        bool stream(ALuint buffer);   // reloads a buffer
        void setStreamPos(float pos);
        float getStreamPos();
        void empty();                 // empties the queue
        void check();                 // checks OpenAL error state
        string errorString(int code); // stringify an error code

    private:

        FILE*           oggFile;       // file handle
        OggVorbis_File  oggStream;     // stream handle
        vorbis_info*    vorbisInfo;    // some formatting data
        vorbis_comment* vorbisComment; // user comments

        ALuint buffers[2]; // front and back buffers
        ALuint source;     // audio source
        ALenum format;     // internal format
        bool m_looping;
};

#endif // __OGGSTREAM_H__
