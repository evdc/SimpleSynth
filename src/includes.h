/**
* includes.h -- for storing all the miscellaneous library includes in one place
* and for any definitions that need to be accessible everywhere,
* since this file will be (directly or indirectly) included from all other files.
*/

#ifndef INCLUDES_H_
#define INCLUDES_H_

#include "portaudio.h"

extern const int sampleRate; //Declare this as extern here (defined in Component.cpp) so that it's accessible from all files that include includes.h (i.e. all of them). Because everything (whether it inherits from Component or not) needs to know the sample rate in order to function, and they all need to use the same one, and it needs to be constant (no downsampling!)

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

//For writing binary files
#include <fstream>

//These are unix-specific? Cross-platform alternatives certainly exist; I haven't looked into them
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//For the sine function
#include <cmath> 

using namespace std;

#endif /*INCLUDES_H_*/
