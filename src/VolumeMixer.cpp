/*
 * VolumeMixer.cpp
 * Implementation of a simple volume mixer
 */

#include "VolumeMixer.h"

#define MAX_INPUTS 16

VolumeMixer::VolumeMixer()
{
    numInputs = 0;
}

void VolumeMixer::addInput(Component *input)
{
    inputs[numInputs] = input;
    numInputs++;
}

float VolumeMixer::getSample(int n)
{
    float outputSample = 0;
    
    //for each input:
    //add its value to the output sample
    for(int i=0; i<numInputs; i++)
    {
        if(inputs[i] != NULL) 
        { 
            outputSample += inputs[i]->getSample(n); 
        }
    }

    //then divide that by the total number of inputs
    if(numInputs > 0)
        outputSample = outputSample / ( (double)numInputs );

    return outputSample;
}
