/*
 *  AudioIO.cpp
 *  Implementation of the AudioIO class, which handle all audio input-output operations.
 *  Serves as a wrapper around PortAudio library functions, acts as an intermediary between them and the rest of the synthesis chain.
 *  Evan D. Crook
 *  Created 1/31/13, 3:43 PM.    
 */

#include "AudioIO.h"

//Standard constructor
AudioIO::AudioIO()
{ 
    numChannels = 2; //Stereo -- mono not currently supported.
    pan = 0.5; //default center
    masterVolume = 1.0; //default max   
    framesPerBuffer = 1024;

    //Initialize PortAudio
    Pa_Initialize();

    //Set the output device to whatever the system's default is
    outputParameters.device = Pa_GetDefaultOutputDevice();
    if (outputParameters.device == paNoDevice) {
      cerr << "Error: No default output device.\n";
    }

    //Set some various PortAudio-related parameters
    outputParameters.channelCount = numChannels;       // stereo output
    outputParameters.sampleFormat = paFloat32; // 32 bit floating point output
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;
    
    //Open the output stream; does not start playing, but prepares it to be used for playing later
    Pa_OpenStream(
              &stream,                  //The address of the stream itself
              NULL,                     //Input parameters (no input)
              &outputParameters,        //The output parameters structure
              sampleRate,               //Number of samples per second
              framesPerBuffer,          //Number of frames (a frame is a set of 2 stereo samples) to write at a time
              paClipOff,                //Don't use clipping
              &AudioIO::paCallBack,     //PortAudio callback function
              this );                   //Userdata is a pointer to this AudioIO object

    Pa_StartStream( stream );

    cout << "PortAudio started: stream opened" << endl;
}

//Destructor
//It is essential this get called somewhere; if PortAudio is started and Pa_Terminate is never called, apparently this can really mess up the system, to the possible extent of your entire computer's audio not working until you reboot. That would be bad
//In other words, make sure to call "delete io" in MainWindow's destructor or similar.
AudioIO::~AudioIO()
{
    Pa_StopStream( stream );

    Pa_CloseStream( stream );

    Pa_Terminate();
    cout << "PortAudio done" << endl;
}

//When this function is called it will start making sound happen (ideally) until stop() is called.
void AudioIO::play() 
{ 
    n = 0; 
    isPlaying = true;
}
//Stop sound currently playing
void AudioIO::stop()
{
    isPlaying = false;
}

//Set functions
void AudioIO::setPan(double value) { pan = value; }
void AudioIO::setMasterVolume(double value) { masterVolume = value; }

/*===============================================================================================================================
===================================================THE CALLBACK ROUTINE==========================================================
Where the magic happens.

AudioIO member function that wraps the PortAudio callback, allowing the callback to have access to AudioIO's methods and data (and thus, an interface with the synthesis chain).
This routine is called (indirectly) by the PortAudio system when it needs new audio data.

IMPORTANT: This routine will run at a very high priority (interrupt level on some sytems), so it is important not to do anything in it
that could block or mess up the system: allocate memory, do file IO, make OS calls, acquire locks on threads. PortAudio documentation was
particularly emphatic about this.

NOTE: Since this will call getSample() on its inputs, which will call getSample() on theirs all the way back down through the synthesis chain,
it is important not to do any memory allocation or file IO in any getSample() function either.
=================================================================================================================================*/
int AudioIO::audioIOCallback( const void *inputBuffer, void *outputBuffer, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags )
{  
    //Do all the synthesis here
    //Do panning here too: take a single input, and turn it into stereo output

    inSample = 0.0;
    lSample = 0.0;
    rSample = 0.0;
 
    float *out = (float*)outputBuffer; //PortAudio requires the buffers passed in as void*; we are going to use it as float*, though, so cast it to that.

    for(i=0; i<frameCount; i++)
    {
        if(isPlaying)
        {
            //Invoke the synthesis chain: get a sample of input by calling on whatever the next component in the chain is to generate one.
            if(inputs[INPUT_DATA] != NULL) { inSample = inputs[INPUT_DATA]->getSample(n); }

            //Apply the master volume control
            inSample *= masterVolume;
            //Perform panning: generate left and right samples
            lSample = inSample*sqrt(1 - pan) * 0.707;
            rSample = inSample*sqrt(pan) * 0.707;
            //Scale by 1/sqrt(2) to keep constant power
        }
        
        //Write to output
        *out++ = lSample;
        *out++ = rSample;

        //Increment the sample counter
        n++;
    }

    return paContinue;
}




float AudioIO::getSample(int n){
    cerr << "Error: attempt to get samples from an AudioIO object: these are supposed to be for writing to wavfiles/sound-output only" << endl;
    return 0;
}

