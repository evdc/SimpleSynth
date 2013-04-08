/* 
 * LFO.h -- Definition of a low-frequency oscillator
 */

#ifndef LFO_H_
#define LFO_H_

#include "Oscillator.h"

class LFO : public Oscillator {
public:
    
    //Constructor
    LFO(double freq=1.0, double amp=0.5, int waveform=0);

    //Get methods
    double getFrequency();
    double getAmplitude();
    int getWaveform();
    //Set methods
    void setFrequency(double);
    void setAmplitude(double);
    void setWaveform(int);


protected:
    //Get an individual sample
    virtual float getSample(int n);    

private:
    double frequency;
    double amplitude;
    int waveform; //0 for sine, 1 for saw, 2 for sqr. (Why would you have a noise LFO?)
	
    double freqMod;
    double ampMod;
    double freqModDepth;
    double moddedFrequency;
    double moddedAmplitude;
    double t;
    int periodInSamples;
    double period;

};

#endif
