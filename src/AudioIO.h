/*
 *  AudioIO.h
 *  Evan D. Crook
 *  Created 1/31/13, 3:43 PM.
 * 
 *  Definitions for the AudioIO class, which shall handle all audio input-output operations:
 *  writing to .wav files, sending audio data to hardware, etc. 
 *  Largely exists as a wrapper around the PortAudio library functions, to integrate them with the synthesis chain.
 *    
 */

#ifndef AUDIOIO_H_
#define AUDIOIO_H_

#include "Component.h"

using namespace std;

class AudioIO : public Component {
public:
	
    //Constructor & Destructor
    AudioIO();	
    ~AudioIO(); //IMPORTANT that this get called (see elaboration in the .cpp) in MainWindow's destructor or similar.

    //Playback control methods -- provide an interface to PA stream control
    void play();    //Method to start stream playback. Call this in a key press event or whenever else you want to start playing sound.
    void stop();    //Method to temporarily stop the stream; does not close and exit PortAudio, that is done in the destructor. Call this in a key release event or whenever else you want to stop playing sound. This will stop ANY sound currently playing.

    //Set functions
    void setPan(double);
    void setMasterVolume(double);

protected:
    //Callback functions. Don't touch these. Protected because what business does an external object have with these? The only thing invoking them is the PortAudio engine.

    //Actual PortAudio callback. Function signature MUST match that specified by PortAudio -- DO NOT change it
    static int paCallBack(const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
    {
        //Yes I am aware you are not supposed to put definitions in a header but when I tried to put it in the .cpp file it didn't link properly
        //and I'm too sleep-deprived to bother figuring out how to make it work properly.
        return ((AudioIO*)userData)->audioIOCallback(input,output,frameCount,timeInfo,statusFlags);
    }

    //Member function callback -- wraps the actual PortAudio callback
    int audioIOCallback( const void *inputBuffer, void *outputBuffer, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags );

    //This is only here because it has to be -- it's inherited from Component, where it's pure virtual, and if AudioIO doesn't implement it then it becomes abstract and cannot be instantiated. Don't try to use it.
    float getSample(int n);

private:
    //Private data members
    int numChannels;
    bool isPlaying;
    bool isReleasing;

    //Sample counter
    int n;
    //Loop counter for buffer loop in callback
    unsigned int i;
    //Used for holding samples & panning/master volume control
    float inSample;
    float lSample;
    float rSample;
    double pan;
    double masterVolume;
    double releaseAmp;    

    //PortAudio-related data members
    PaStreamParameters outputParameters;
    PaStream *stream;
    int framesPerBuffer;
};	

#endif /*AUDIOIO_H_*/
