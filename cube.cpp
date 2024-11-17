#include "matrixMul.hpp"
#include "helpers.hpp"
#include "screen.hpp"
#include <unistd.h>

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
        {-std::sin(yRot),0,std::cos(yRot)}
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


void render(int width, int height, double** depthBuffer) {
    std::string **screen = new std::string*[height];
    for (int i = 0; i < height; i++) {
        screen[i] = new std::string[width];
    }

    double coords2D[8][4] = {0};
    double aspect = (double)width/height;

    project2D(1, 90, aspect, 20, 1, coords2D);    
    
    for(int i=0; i<height; i++) {
        for(int z=0; z<width; z++) {
            screen[i][z] = " ";
        }
    }

    for (int j = 0; j < height; j++) {
        int screenX = coords2D[j][0]/2 *(width-1);
        int screenY = coords2D[j][1]/2 *(height-1);

        double depth = coords2D[j][2];
        if (screenX >= 0 && screenX < width &&
        screenY >= 0 && screenY < height) {
            if (depth < depthBuffer[screenY][screenX]) {
                screen[screenY][screenX] = "@";
                depthBuffer[screenY][screenX] = depth; 
            }
        }
    }

    for (int i = 0; i < 12; i++) {
        int v1 = edges[i][0];
        int v2 = edges[i][1];

        int screenX1 = (coords2D[v1][0] + 1) / 2 * (width - 1);  
        int screenY1 = (coords2D[v1][1] + 1) / 2 * (height - 1); 
        int screenX2 = (coords2D[v2][0] + 1) / 2 * (width - 1);
        int screenY2 = (coords2D[v2][1] + 1) / 2 * (height - 1);

        drawLine(screenX1, screenY1, screenX2, screenY2, screen, height, width);
    }

    // for (int i = 0; i < 6; i++) {
    //     fillFace(faces[i][0], faces[i][1], faces[i][2], faces[i][3], height, width, coords2D, screen, depthBuffer);
    // }  


    for(int i=0; i<height; i++) {
        for(int z=0; z<width; z++) {
            std::cout << screen[i][z];
        }
        std::cout << "\n";
    }
}

int main() {
    double delta_x = deg2Rad(10);
    double delta_y = deg2Rad(40);
    double delta_z = deg2Rad(0);

    int width = 40;
    int height = 20;

    double** depthBuffer = initBuffer(width, height);

    while (1) {
        // std::cout << "points before transformation\n"; 
        applyTransform(delta_x, delta_y, delta_z);
        render(width, height, depthBuffer);

        std::cout << "\033[2J\033[1;1H"; 
        usleep(100000); 
    }
}


