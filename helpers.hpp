#ifndef COORDS
#define COORDS
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

    int rotationSpeed = 1;

};
extern cubeCoords cube;

#endif
