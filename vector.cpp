#include "vector.hpp"

// vector and matrix methods used within cube.cpp
// apply matrix to cube coordinates C_n = (R * C)

void applyRotation1d(cubeCoords cubeInfo, int** rotMatrix) {
    // run over all 8 coordinates of cube
    for(int x=0; x<8; x++) {
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                cubeInfo.coords[x][j] *= rotMatrix[i][j];
            }  
        }  
    }
}

// matmul for 3d
int** matrixMul3D(int** matrix1, int** matrix2) {
    int res[3][3] = {0};

    for(int i=0; i<3;i++) {
        for(int j=0; j<3;j++) {
            for(int x=0; x<3;x++) {
                res[i][j] += matrix1[i][x] + matrix2[x][j];
            } 
        }
    }
    return res; 
}



        



