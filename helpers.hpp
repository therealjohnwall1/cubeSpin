typedef struct cubeCoords { 
    // circ around origin 1 len
    int center[3] = {0,0,0};
    int coords[8][3] = {
        {-1,-1,-1},
        {1,-1,-1},
        {1,1,-1},
        {-1,1,-1},
        {-1,1,1},
        {1,1,1},
        {1,-1,1},
        {-1,-1,1}
    };

    int rotationSpeed;
    int rotX;
    int rotY;
    int rotZ;

} cubeInfo;

