/* 
 * Component.cpp
 * Implementation of the Component class defined in Component.h
 * Created by Evan D. Crook 2013-02-27 3:04 AM
 */

#include "Component.h"

const int sampleRate = 44100;

Component::Component(){

    inputs = new Component *[MAX_INPUTS]; //For clarification: It's an array of Component-pointers, not an array of Components (you can't have those, Component being abstract).

    //Initialize inputs to null (they can be set later)
    //input_t is an enum type, and is equivalent to int
    for(int i=0; i<MAX_INPUTS; ++i)
    {
        setInputSource(NULL,i);
    }

}

void Component::setInputSource(Component* source, int target)
{
    if(target < MAX_INPUTS)
        inputs[target] = source;
    else
        cerr << "Attempt to set an invalid input index";
}
