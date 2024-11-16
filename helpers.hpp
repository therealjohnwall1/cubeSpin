#pragma once
#include <string>
#include <math.h>

#define deg2Rad(x) x*(M_PI/180)
#define rad2Deg(x) x*(180/M_PI)

struct cubeCoords { 
    // circ around origin 1 len
    double center[3] = {0,0,0};
	
	// final coord used for homogenous coords(will always be 1)
    double coords[8][4] = {
        {-1,-1,-1,1},
        {1,-1,-1,1},
        {1,1,-1,1 },
        {-1,1,-1,1},
        {-1,1,1,1},
        {1,1,1,1},
        {1,-1,1,1},
        {-1,-1,1,1}
    };
};
extern cubeCoords cube;


