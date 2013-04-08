/*
 * VolumeMixer.h
 * Definition of a simple volume mixer -- mixes input signals and scales amplitude to fit in the range [-1 1]
 */

#ifndef VOLUMEMIXER_H_
#define VOLUMEMIXER_H_

#include "Component.h"

class VolumeMixer : public Component {
public:

    //Constructor
    VolumeMixer();

    //Add/remove inputs from the list
    //Note: this functionality is different enough from Component::setInputSource(Component *,int) to be worth defining a new function for.
    void addInput(Component *input);

protected:
    
    //Get an individual sample; implementation of pure virtual fn. from Component
    virtual float getSample(int n);

private:

    //Number of input channels that have been set
    int numInputs;
};

#endif
