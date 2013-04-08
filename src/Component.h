/*
 * Component.h
 * Definition for the Component class - an abstract base class from which all components (e.g. Oscillators, Filters, VolumeControls...) inherit
 * Allows for flexibility in the synthesis chain (e.g. a Filter, Oscillator, AudioIO etc. can take any Component as input)
 * Created by Evan D. Crook 2013-02-27 2:50 AM
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "includes.h"

//8-channel recording is fairly common (though 16 is moreso), way more than this will need anyway
#define MAX_INPUTS 8

class Component {
public:

    //Enumerate the various types of inputs a component can have
    enum input_t {  INPUT_DATA, //0
                    INPUT_FREQUENCY, //1
                    INPUT_AMPLITUDE, //2
                    INPUT_EXTRA //3
                 };

    //Set an input source from which to get data, either audio data for processing, or modulation data for control.
    virtual void setInputSource(Component* source, int target);	

    //Pure virtual function: it is up to derived classes to implement this function.
    virtual float getSample(int n) = 0;
    
protected:
//These are protected, not private, because derived classes need them
   
    Component();     

    Component **inputs; //Array of Component pointers -- stores (pointers to) this component's inputs.

};

#endif /*COMPONENT_H_*/
