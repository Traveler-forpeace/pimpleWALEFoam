# description

This solver is based on pimpleFoam, it calculates TKE and dissapation rate for LES using WALE model, but it is also suitable for LES using Smagorinsky model.

It can be compiled successfully in OpenFOAM-v10, but some modifications may be required for other versions.  

# useage

## compile

1. make a dictionary named applications at "$FOAM_RUN/..", eg "/home/usr/OpenFOAM/usr-10/applications"
2. clone this repository to the applications dictionary
3. use "wmake" to compile it

## case settings

1. use application "pimpleWALEFoam"
2. add OpenFOAM's fieldAverage function in case, this solver needs it to get UMean, then calculates Uprime.
