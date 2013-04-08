/*
 * Oscillator.h
 * Definitions for the Oscillator class
 * For now, it only does sine waves.
 */

#ifndef OSCILLATOR_H_
#define OSCILLATOR_H_

#include "Component.h"
#include "Wavetable.h"

class Oscillator : public Component {
public:
	
    //Constructor
    Oscillator(double freq=440, double amp=1.0, int waveform=0); //See notes in Oscillator.cpp regarding mod depth.
   
    //Tell the oscillator where to find the wavetables it is going to use
    void setWaveformTable(int waveform,Wavetable* table);

    //Get methods
    double getFrequency();
    double getAmplitude();
    int getWaveform();
    //Set methods
    void setFrequency(double);
    void setFrequencyDetune(int);
    void setBaseFrequency(double);
    void setAmplitude(double);
    void setWaveform(int);

protected:
    //Get an individual sample
    virtual float getSample(int n);

private:
    double frequency;
    double baseFrequency;
    int detuneSemitones;
    double amplitude;
    int waveform; //0 for sine, 1 for saw, 2 for sqr; -1 for noise.
	
    double freqMod;
    double ampMod;
    double freqModDepth;
    double moddedFrequency;
    double moddedAmplitude;
    float sample;    

    int phase; //accumulator
    int phaseInc; //counter
    int tableSize;
    
    double t;
    int periodInSamples;
    double period;

    Wavetable **waveTables; //Array of Wavetable pointers -- stores available wavetables
};  

#endif /*OSCILLATOR_H_*/
