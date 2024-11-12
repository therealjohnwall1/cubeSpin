#include "matrixMul.hpp"

// config stuff for cube
cubeCoords cube;

// 3d transformations
void applyTransform(double xRot, double yRot, double zRot) {
    // define x,y,z matricies
    
    double rotX[3][3] = {
        {1, 0, 0},
        {0, std::cos(xRot),-std::sin(xRot)},
        {0, std::sin(xRot),std::cos(xRot)}
    };

    double rotY[3][3] = {
        {std::cos(yRot), 0,std::sin(yRot)},
        {0,1,0},
        {0,std::sin(yRot),std::cos(yRot)}
    };

    double rotZ[3][3] = {
        {std::cos(zRot), -std::sin(zRot), 0},
        {std::sin(zRot), std::cos(zRot), 0},
        {0,0,1}
    };

    // combine them to get cumulative rotations intrinsic(R_x * R_y * R_z)

    double xMuly[3][3] = {0};
    double totRot[3][3] = {0};
   
    matrixMul3D(rotX,rotY, xMuly);

    for(int i = 0; i < 3; i++) {
        for(int j=0; j < 3;j++) {
            std::cout << xMuly[i][j] << ", ";
        }   
        std::cout <<"\n";
    }   
    matrixMul3D(xMuly, rotZ, totRot);
    
   // apply total rotation onto coordinates 
    applyRotation(totRot);
} 

void echoState() {
	for(int i=1;i<9;i++) {
        std::cout << "coord num: " << i  << "   " << cube.coords[i-1][0] << "," <<
        cube.coords[i-1][1] << "," << cube.coords[i-1][2] << "depth: " << cube.coords[i-1][3] <<"\n";
    }   
}

void render(int width, int height) {
    std::string screen[width][height];
    double coords2D[8][4] = {0};
    project2D(1,90,30,10,5,coords2D);    

    for(int p=0; p<8; p++) {
        coords2D[p][0] = (coords2D[p][0] + 1)/2 * (width-1);
        coords2D[p][1] = (1 - coords2D[p][1])/2 * (height-1);
    }   

    std::cout << "normalzied points + upscale to pic\n";
    for (int j = 0; j < 8; j++) {
        for (int x = 0; x < 4; x++) {
            std::cout << coords2D[j][x] << ",";
        }
        std::cout << "\n";
    }
    
    for(int i=0; i<height; i++) {
        for(int z=0; z<width; z++) {
            screen[i][z] = "0";
        }
    }

    for (int j = 0; j < 8; j++) {
        screen[(int)coords2D[j][1]][(int)coords2D[j][0]] = "@";
    }

    for(int i=0; i<height; i++) {
        for(int z=0; z<width; z++) {
            std::cout << screen[i][z];
        }
        std::cout << "\n";
    }
}

int main() {
    //applyTransform(100,10,0);
    echoState();
    render(10,10);
}
