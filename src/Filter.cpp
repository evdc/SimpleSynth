/*
 * Filter.cpp
 * Implementation of a second-order Butterworth filter (low-pass or high-pass)
 * Created by Evan D. Crook, 2013-03-02
 */

#include "Filter.h"

Filter::Filter(double cut, int type) : cutoff(cut), filterType(type)
{
    //Using a 2-pole (2nd-order) filter: this is fixed, because higher-order filters get far more complicated.
    //It would be nice to implement higher-order filters, and let the user choose order; but 2nd-order works well enough, and time is an issue.
    numPoles = 2;

    //Initialize the arrays for storing previous inputs/outputs
    x = new double[numPoles + 1];
    y = new double[numPoles + 1];

    //Initialize the coefficient arrays
    a = new double[numPoles + 1]();
    b = new double[numPoles + 1]();

    //Compute the coefficients based on filter type: 0 for low-pass, 1 for high-pass. (To do band-pass, chain LP and HP filters together?)
    //These inputs will need to be validated, ie constrain them to 0 and 1.
    if(filterType == 0) { computeLPCoefficients(cutoff); } //Low-pass 
    else if(filterType == 1) { computeHPCoefficients(cutoff); } //High-pass

    enabled = true;
}

void Filter::computeLPCoefficients(double cut)
{

    //Determine the coefficients a[k] and b[k] for a second-order Butterworth low-pass filter,
    //using a bilinear transform.
    //Reference: Digital Signal Processing, by W. Stanley, G. Dougherty and R. Dougherty (1984).

    //Temp constants. Naming follows notation convention from the textbook.
    double C = 1/tan(M_PI*cut/sampleRate);
    double A = 1 + M_SQRT2*C + C*C;    

    //a[k] constants: applied to inputs
    a[0] = 1 / A;
    a[1] = 2 / A;
    a[2] = 1 / A;

    //b[k] constants: applied to outputs
    b[1] = (2 - 2*C*C) / A;
    b[2] = (1 - M_SQRT2*C + C*C) / A;
}

void Filter::computeHPCoefficients(double cut)
{
    //Determine the coefficients a[k] and b[k] for a second-order Butterworth high-pass filter.
    
    //Temp constants
    double C = 1/tan(M_PI*cut/sampleRate);
    double A = 1 + M_SQRT2*C + C*C;    

    //a[k] constants: applied to inputs
    a[0] = C*C / A;
    a[1] = -2*C*C / A;
    a[2] = C*C / A;

    //b[k] constants: applied to outputs
    b[1] = (2 - 2*C*C) / A;
    b[2] = (1 - M_SQRT2*C + C*C) / A;
}

//Generate an individual sample of filtered output.
//This will be called by whatever's next in the synthesis chain.
//NOTE: Since this is, ultimately, called in the PortAudio callback, do not allocate memory, do file I/O or make OS calls in this function. 
//Implementation of the pure virtual function getSample(double) inherited from Component.
float Filter::getSample(int n)
{
    sample = 0.0;
    if(inputs[INPUT_DATA]!=NULL) { sample = inputs[INPUT_DATA]->getSample(n); }

    if(!enabled)
        return sample; //If enabled is false, pass input directly to output and return.

    if(inputs[INPUT_FREQUENCY] != NULL )  //Modulate the cutoff frequency
    { 
        cutoffMod = inputs[INPUT_FREQUENCY]->getSample(n);
        modDepth = cutoff * 0.5;
        moddedCutoff = cutoff + cutoffMod*modDepth;
        //cout << "Filter cutoffMod: " << cutoffMod << " moddedCutoff: " << moddedCutoff << endl;
        if(filterType == 0) { computeLPCoefficients(moddedCutoff); } //Low-pass 
        else if(filterType == 1) { computeHPCoefficients(moddedCutoff); } //High-pass 
    }

    //Move inputs
    x[2] = x[1]; x[1] = x[0];
    x[0] = sample;
    //move outputs
    y[2] = y[1]; y[1] = y[0];    

    //Perform filtering, according to the difference equation:
    //y[n] = a[0]x[n] + a[1]x[n-1] + a[2]x[n-2]
    //          - b[1]y[n-1] - b[2]y[n-2]
    //x[n] is the record of previous inputs, y[n] is the record of previous outputs
    filteredSample = a[0]*x[0] + a[1]*x[1] + a[2]*x[2]
                        - b[1]*y[1] - b[2]*y[2];
    y[0] = filteredSample;
    
    return filteredSample;
}


void Filter::setCutoff(double cut)
{
    cutoff = cut;

    //The filter coefficients are specific to a given cutoff frequency, so they have to be recomputed every time the cutoff frequency is changed.
    if(filterType == 0) { computeLPCoefficients(cutoff); } //Low-pass 
    else if(filterType == 1) { computeHPCoefficients(cutoff); } //High-pass 
}

//Various trivial get and set methods
double Filter::getCutoff() { return cutoff; }
void Filter::setEnabled(bool value) { enabled = value; }
void Filter::setType(int value) 
{ 
    filterType = value;
    if(filterType == 0) { computeLPCoefficients(cutoff); } //Low-pass 
    else if(filterType == 1) { computeHPCoefficients(cutoff); } //High-pass 
    
} //note: no error checking performed

