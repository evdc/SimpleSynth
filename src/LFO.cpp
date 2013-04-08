/*
 * LFO.cpp
 * Implementation of a low-frequency oscillator
 */

#include "LFO.h"

LFO::LFO(double freq, double amp, int wave) : frequency(freq), amplitude(amp), waveform(wave)
{
    period = 1/frequency;
}

//Generate an individual sample of a waveform.
//This will be called by whatever's next in the synthesis chain (i.e. a Filter, an Oscillator ...)
//NOTE: Since this is, ultimately, called in the PortAudio callback, do not allocate memory, do file I/O or make OS calls in this function. 
//Implementation of the pure virtual function getSample(double) inherited from Component.
float LFO::getSample(int n)
{
    //Get modulation data from whatever components have been set as sources of modulation data
    freqMod = 0.0;
    ampMod = 0.0;
    if(inputs[INPUT_FREQUENCY] != NULL) { freqMod = inputs[INPUT_FREQUENCY]->getSample(n); }    
    if(inputs[INPUT_AMPLITUDE] != NULL) { ampMod = inputs[INPUT_AMPLITUDE]->getSample(n); }
    freqModDepth = 2;
    moddedFrequency = frequency + freqModDepth*freqMod;
    moddedAmplitude = amplitude - abs(ampMod);
    
    //LFO's use directly-generated waveforms, since wavetables (as implemented here) don't support frequencies below 22 Hz.
    //The aliasing in directly-generated waves is not a problem with LFO's, since they aren't heard directly.

    t = (double)n/( (double)sampleRate );
    if(waveform == 0) //sine
    {
        return moddedAmplitude * sin( frequency*(2*M_PI*t) + freqMod);
    }
    else if(waveform == 2) //square
    {
        period = 1/moddedFrequency;
        periodInSamples = (int)floor(period*sampleRate);
        if( (n%periodInSamples) < 0.5*periodInSamples) { return 1*moddedAmplitude; }
        else { return -1*moddedAmplitude; }
    }
    else if(waveform == 1) //saw
    {
        period = 1/moddedFrequency;
        return moddedAmplitude*2*( t/period - floor(.5+t/period) );
    }
    else
    {
        return 0;
    }
    
}

//Get methods
double LFO::getFrequency() { return frequency; }
double LFO::getAmplitude() { return amplitude; }
int LFO::getWaveform() { return waveform; }
//Set methods
void LFO::setFrequency(double value) { frequency = value; }
void LFO::setAmplitude(double value) { amplitude = value; }
void LFO::setWaveform(int value) { waveform = value; }

