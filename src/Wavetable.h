/*
 * Wavetable.h
 * Definition of a wavetable class, which pre-computes and stores a set of samples for an Oscillator to use
 * (or anything else, theoretically, but probably only an Oscillator at least for right now)
 */

#ifndef WAVETABLE_H
#define WAVETABLE_H

#include "Component.h"

class Wavetable {
public:
    
    //Constructor
    Wavetable(int tableSize=32767);

    //Build the table from a set of sines
    void addSines(int numPasses, int increment, int phaseShift); //sine: 1,1,1 saw: 21,1,-1 square: 10,2,1

    //Get a value from the table
    float getValue(int index);

    //get methods
    int getTableSize();

private:

    //The actual wavetable: array of (float) samples
    int tableSize;
    float * table;
};

#endif
