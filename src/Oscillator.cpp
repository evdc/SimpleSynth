/*
 *  Oscillator.cpp
 *  Implementation of the Oscillator class
 *  Uses wavetable synthesis
 */
 
#include "Oscillator.h"
 
//Constructor -- set data members, initialize wavetable
Oscillator::Oscillator(double freq, double amp, int wave) : frequency(freq), amplitude(amp), waveform(wave) {
    baseFrequency = frequency;
    detuneSemitones = 0;
    phase = 0;
    phaseInc = 0;
    waveTables = new Wavetable *[3];
    freqModDepth = 0.22462; //Width of two semitones (one whole-step)
}	

//Generate an individual sample of a waveform.
//This will be called by whatever's next in the synthesis chain (i.e. a Filter, an VolumeMixer, an AudioIO...)
//NOTE: Since this is, ultimately, called in the PortAudio callback, do not allocate memory, do file I/O or make OS calls in this function. 
//Implementation of the pure virtual function getSample(double) inherited from Component.
float Oscillator::getSample(int n)
{

    //Get modulation data from whatever components have been set as sources of modulation data
    freqMod = 0.0;
    ampMod = 0.0;    
    if(inputs[INPUT_FREQUENCY] != NULL) { freqMod = inputs[INPUT_FREQUENCY]->getSample(n); }
    if(inputs[INPUT_AMPLITUDE] != NULL) { ampMod = inputs[INPUT_AMPLITUDE]->getSample(n); }
    //Process modulation data a bit    
    moddedFrequency = frequency + (frequency*freqModDepth)*freqMod;
    moddedAmplitude = amplitude - abs(ampMod);

    //If set to generate noise, skip the wavetable step and do that instead
    if(waveform == -1) //used to represent "Waveform = noise"
    {
        //Generate "White noise": samples of uniformly distributed random heights
        double randomValue = ( (double)rand()/(double)RAND_MAX ); //0 to 1
        randomValue = (randomValue*2)-1; //-1 to 1
        return moddedAmplitude * randomValue;
    }

    //Otherwise, perform wavetable synthesis
    tableSize = waveTables[waveform]->getTableSize();
    phaseInc = (int)floor( ( tableSize/(double)sampleRate )*moddedFrequency ); // (N/Fs * f) formula for phase
    sample = (waveTables[waveform])->getValue(phase);                    // Get a sample from the wavetable corresponding to the current waveform
    phase += phaseInc;                                                   // increment phase counter
    if (phase >= tableSize) { phase -= tableSize; }                      // wrap around, remain within bounds of table

    return moddedAmplitude * sample; 
    //return sample;
} 

void Oscillator::setWaveformTable(int waveform, Wavetable* table)
{
    waveTables[waveform] = table;
}

//Get methods
double Oscillator::getFrequency() { return frequency; }
double Oscillator::getAmplitude() { return amplitude; }
int Oscillator::getWaveform() { return waveform; }
//Set methods
void Oscillator::setFrequency(double value) { frequency = value; }
void Oscillator::setBaseFrequency(double value) 
{ 
    baseFrequency = value; 
    frequency = baseFrequency*pow(2, ((double)detuneSemitones/12.0) ); //recompute the frequency since the base has changed
    //cout << "baseFrequency: " << baseFrequency << " frequency: " << frequency << endl;
}
void Oscillator::setAmplitude(double value) { amplitude = value; }
void Oscillator::setWaveform(int value) { waveform = value; }

void Oscillator::setFrequencyDetune(int semitones)
{
    detuneSemitones = semitones;
    frequency = baseFrequency*pow(2, ( (double)detuneSemitones/12.0) );
    //cout << "baseFrequency: " << baseFrequency << " frequency: " << frequency << endl;
}


