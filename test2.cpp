#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

using namespace std;

ALuint Buffer; // Buffers hold sound data.

ALuint Source; // Sources are points emitting sound.

// Position of the source sound.
ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };
// Velocity of the source sound.
ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };
// Position of the listener.
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
// Velocity of the listener.
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
// Orientation of the listener. (first 3 elements are "at", second 3 are "up")
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };


ALboolean LoadALData();
void SetListenerValues();
void KillALData();

int main(int argc, char **argv)
{
    alutInit(&argc, argv);
    alGetError();

    cout << "init ALUT!\n";

    // Load the wav data.
    if (LoadALData() == AL_FALSE)
        return -1;

    cout << "load data!\n";

    SetListenerValues();

    // Begin the source playing.
    alSourcePlay(Source);

    // Loop
    ALint time = 0;
    ALint elapse = 0;

    while (!kbhit())
    {
        elapse += clock() - time;
        time += elapse;

        if (elapse > 50)
        {
            elapse = 0;

            SourcePos[0] += SourceVel[0];
            SourcePos[1] += SourceVel[1];
            SourcePos[2] += SourceVel[2];

            alSourcefv(Source, AL_POSITION, SourcePos);
        }
    }


    //Exit procedure.
    KillALData();

    return 0;
}

ALboolean LoadALData()
{
    // Variables to load into.

    ALenum format;
    ALsizei size;
    ALvoid* data;
    ALsizei freq;
    ALboolean loop;

    Buffer = alutCreateBufferFromFile("explosion.wav");
/*
    // Load wav data into a buffer.
    alGenBuffers(1, &Buffer);
    if (alGetError() != AL_NO_ERROR)
        return AL_FALSE;

    alutLoadWAVFile((ALbyte*)("explosion.wav"), &format, &data, &size, &freq, &loop);
    alBufferData(Buffer, format, data, size, freq);
    alutUnloadWAV(format, data, size, freq);
*/
    // Bind buffer with a source.
    alGenSources(1, &Source);

    if (alGetError() != AL_NO_ERROR)
        return AL_FALSE;

    alSourcei (Source, AL_BUFFER,   Buffer   );
    alSourcef (Source, AL_PITCH,    1.0f     );
    alSourcef (Source, AL_GAIN,     1.0f     );
    alSourcefv(Source, AL_POSITION, SourcePos);
    alSourcefv(Source, AL_VELOCITY, SourceVel);
    alSourcei (Source, AL_LOOPING,  AL_TRUE  );

    // Do another error check and return.
    if (alGetError() == AL_NO_ERROR)
        return AL_TRUE;

    return AL_FALSE;
}

void SetListenerValues()
{
    alListenerfv(AL_POSITION,    ListenerPos);
    alListenerfv(AL_VELOCITY,    ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);
}

void KillALData()
{
    alDeleteBuffers(1, &Buffer);
    alDeleteSources(1, &Source);
    alutExit();
}
