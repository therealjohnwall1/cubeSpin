#include "matrixMul.hpp"
#include "helpers.hpp"

// vector and matrix methods used within cube.cpp
// apply matrix to cube coordinates C_n = (R * C)

void vecMatrixMul3D(double vec[4], double rotMatrix[3][3], double res[4]) {
    for(int i=0; i<3;i++) {
        for(int j=0; j<3;j++) {
            res[i] += vec[j] * rotMatrix[i][j];
        }
    }
}

void applyRotation(double rotMatrix[3][3]) {
    for(int x=0; x<8; x++) {
        double res[4] = {0};
        vecMatrixMul3D(cube.coords[x], rotMatrix, res);

        for (int i = 0; i < 3; i++) {
            cube.coords[x][i] = res[i];
        }
    }
}

void applyProjection(double vec[4], double projMatrix[4][4], double vec2d[4]) {
    for(int i=0; i<4;i++) {
        for(int j=0; j<4;j++) {
            vec2d[i] += vec[j] * projMatrix[i][j];
        }
    }
}

void matrixMul3D(double matrix1[3][3], double matrix2[3][3], double ans[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int x = 0; x < 3; x++) {
                ans[i][j] += matrix1[i][x] * matrix2[x][j];  
            }
        }
    }
}

// camera functions 
void project2D(double scaleFactor, double fov, double aspect, double far, double near, double coords2D[8][4]) {
    fov = deg2Rad(fov)/2;

    double projMat[4][4] = {
        {1/(aspect * std::tan(fov)),0,0,0},
        {0,std::atan(fov), 0,0},
        {0,0,-(far + near)/(far-near), -(2*far*near)/(far-near)},
        {0, 0, -1, 0}
    };
    
    for(int i=0; i<8;i++) {
        double vec2d[4] = {0};
        applyProjection(cube.coords[i], projMat, vec2d);

        for(int z=0;z<3;z++) {
           coords2D[i][z] = vec2d[z]; 
        }   
    }
}


