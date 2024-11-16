#include "matrixMul.hpp"
#include "helpers.hpp"
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

void drawLine(int x0, int y0, int x1, int y1, std::string** screen, int height, int width) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
    int err = dx + dy, e2; 

    while (true) {
        if (x0 >= 0 && x0 < width && y0 >= 0 && y0 < height) {
            screen[y0][x0] = "@";
        }
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void render(int width, int height) {
    // std::string screen[height][width];
    std::string **screen = new std::string*[height];
    for (int i = 0; i < height; i++) {
        screen[i] = new std::string[width];
    }

    double coords2D[8][4] = {0};
    double aspect = (double)width/height;


    project2D(1, 90, aspect, 20, 1, coords2D);    

    std::cout << "coords2d after projection matrix: \n";
    for(int i=0;i<8;i++) {
        std::cout << (int)coords2D[i][0] << "," << (int)coords2D[i][1] << "," << (int)coords2D[i][2] << "," << (int)coords2D[i][3] << "\n";
    }    
    
    for(int i=0; i<height; i++) {
        for(int z=0; z<width; z++) {
            screen[i][z] = " ";
        }
    }

    for (int j = 0; j < height; j++) {
        int screenX = coords2D[j][0]/2 *(width-1);
        int screenY = coords2D[j][1]/2 *(height-1);
        if (screenX >= 0 && screenX < width &&
        screenY >= 0 && screenY < height) {
            screen[screenY][screenX] = "@";
        }
    }
    // cube edges
    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},  // Bottom face
        {4, 5}, {5, 6}, {6, 7}, {7, 4},  // Top face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}   // Vertical edges
    };

    for (int i = 0; i < 12; i++) {
        int v1 = edges[i][0];
        int v2 = edges[i][1];

        int screenX1 = (coords2D[v1][0] + 1) / 2 * (width - 1);  
        int screenY1 = (coords2D[v1][1] + 1) / 2 * (height - 1); 
        int screenX2 = (coords2D[v2][0] + 1) / 2 * (width - 1);
        int screenY2 = (coords2D[v2][1] + 1) / 2 * (height - 1);

        // Call drawLine to connect the vertices
        drawLine(screenX1, screenY1, screenX2, screenY2, screen, height, width);
    }


    for(int i=0; i<height; i++) {
        for(int z=0; z<width; z++) {
            std::cout << screen[i][z];
        }

        std::cout << "\n";
    }
}

int main() {
    int delta_x = deg2Rad(0);
    int delta_y = deg2Rad(0);
    int delta_z = deg2Rad(0);

    while (1) {
        std::cout << "points before transformation\n"; 
        // offsetCube(10);
        echoState();
        applyTransform(delta_x, delta_y, delta_z);
        std::cout << "points after transformation\n"; 
        echoState();

        render(20,10);
        sleep(2);
        std::cout << "\n";
    }
}


