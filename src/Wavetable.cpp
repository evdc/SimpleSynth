/*
 * Wavetable.cpp
 * Implementation of a simple Wavetable
 */

#include "Wavetable.h"

Wavetable::Wavetable(int size) : tableSize(size)
{ 
    table = new float[tableSize+1]();
}

void Wavetable::addSines(int numPasses, int increment, int phaseShift)
{
/*
    //Method 1
    double fundFreq = ((double)sampleRate)/((double)tableSize);
    double multiplier = 1;
    double t = 0;
    for(int i=0; i<numPasses; i++)
    {
        for(int j=0; j<(tableSize+1); j++)
        {
            t = j/((double) sampleRate);
            table[j] += (1/multiplier)*sin(fundFreq*2*M_PI*t*multiplier);
        }
        multiplier += increment;
        multiplier *= phaseShift;
    }
*/
    //Method 2
    double fundFreq = ((double)sampleRate)/((double)tableSize);
    double t = 0;
    for(int i=0; i<(tableSize+1); i++)
    {
        t = i/((double) sampleRate);
        for(int j=1; j<=numPasses; j += increment)
        {
            double k = (double)j;
            table[i] += (2*increment/M_PI) * pow(phaseShift,k+1) * (1/k) * sin(2*M_PI*fundFreq*t*k);
        }  
    }
//*/
    table[tableSize+1] = table[0];
}

float Wavetable::getValue(int index)
{
    if(index >= 0 && index <= tableSize)
        return table[index];
    else
        return 0;
}

int Wavetable::getTableSize() { return tableSize; }
