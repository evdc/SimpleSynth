/*
 * Filter.h
 * Specification of a second-order Butterworth filter (low-pass or high-pass).
 * Created by Evan D. Crook, 2013-03-02
 */

#ifndef FILTER_H_
#define FILTER_H_

#include "Component.h"

class Filter : public Component {
public:
    
    //Constructor
    Filter(double cutoff, int type=0);

    //Get and set
    double getCutoff();
    void setCutoff(double cutoff);
    void setEnabled(bool value);
    void setType(int value);

protected:
    //Compute the coefficients for the current cutoff frequency
    //Protected because these are used internally, and why would an external object need to force recomputing of filter coefficients?
    void computeLPCoefficients(double cutoff);
    void computeHPCoefficients(double cutoff);

    //Get an individual sample; implement the pure virtual function inherited from Component.
    float getSample(int n);

private:
    double cutoff;
    int numPoles;
    int filterType; //0 for lowpass, 1 for highpass
    bool enabled;

    //Store the previous inputs & outputs
    double * x;
    double * y;

    //Store the coefficients
    double * a;
    double * b;

    //Variables used in getSample() -- allocated here, so as not to allocate memory in callback
    double cutoffMod;
    double modDepth;
    double moddedCutoff;
    float sample;
    float filteredSample;
};

#endif /* FILTER_H_ */
