#include "matrixMul.hpp"
#include "helpers.hpp"

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
    //std::cout << "vec: " << vec[0] << "," << vec[1] << "," << vec[2] << "," << vec[3] << "\n";

    for(int i=0; i<4;i++) {
        for(int j=0; j<4;j++) {
            vec2d[i] += vec[j] * projMatrix[i][j];
        }
    }
    // std::cout << "vec2d(transform): " << vec2d[0] << "," << vec2d[1] << "," << vec2d[2] << "," << vec2d[3] << "\n";

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

void project2D(double scaleFactor, double fov, double aspect, double far, double near, double coords2D[8][4]) {
    fov = deg2Rad(fov)/2;
    double test = 1/(aspect* std::tan(fov));
    std::cout << "aspect: " << test << "\n";

    double projMat[4][4] = {
        {1/(aspect * std::tan(fov)),0,0,0},
        {0,1/std::tan(fov), 0,0},
        {0,0,-(far + near)/(far-near), -(2*far*near)/(far-near)},
        {0, 0, -1, 0}
    };
    
    // std::cout << "vec2d before norm: ";   
    for(int i=0; i<8;i++) {
        double vec2d[4] = {0};
        applyProjection(cube.coords[i], projMat, vec2d);

        // for(int i=0;i<8;i++) {
        //     std::cout << (int)coords2D[i][0] << "," << (int)coords2D[i][1] << "," << (int)coords2D[i][2] << "," << (int)coords2D[i][3] << "\n";
        //  }    
        
        coords2D[i][0] = vec2d[0]/vec2d[3]; 
        coords2D[i][1] = vec2d[1]/vec2d[3]; 
        coords2D[i][2] = vec2d[2]/vec2d[3]; 
        coords2D[i][3] = vec2d[3]; 
    }
}

void offsetCube(int offset) {
    for (int i = 0; i < 8; i++) {
        cube.coords[i][2] += offset; 
    }
}

