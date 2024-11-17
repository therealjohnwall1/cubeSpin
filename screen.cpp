#include "screen.hpp"

int edges[12][2] = {
    {0, 1}, {1, 2}, {2, 3}, {3, 0},  
    {4, 5}, {5, 6}, {6, 7}, {7, 4},  
    {0, 4}, {1, 5}, {2, 6}, {3, 7}   
};

int faces[6][4] = {
    {0, 1, 2, 3}, 
    {4, 5, 6, 7}, 
    {0, 3, 7, 4}, 
    {1, 2, 6, 5}, 
    {3, 2, 6, 7}, 
    {0, 1, 5, 4}  
};

double** initBuffer(int width, int height) {
    double** depthBuffer = new double*[height];
    for (int i = 0; i < height; i++) {
        depthBuffer[i] = new double[width];
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            depthBuffer[i][j] = std::numeric_limits<double>::infinity(); 
        }
    }

    return depthBuffer;
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

void fillFace(int v0, int v1, int v2, int v3, int height, int width, double coords2D[8][4], std::string** screen, 
        double** depthBuffer) {
    fillTriangle(v0, v1, v2, coords2D, height, width, screen, depthBuffer);
    fillTriangle(v0, v2, v3, coords2D, height, width, screen, depthBuffer);
}

// todo: fix rasterization
void fillTriangle(int v0, int v1, int v2, double coords2D[8][4], int height, int width, 
        std::string** screen,double** depthBuffer) {
    int x0 = coords2D[v0][0] / 2 * (width - 1);
    int y0 = coords2D[v0][1] / 2 * (height - 1);
    double z0 = coords2D[v0][2];

    int x1 = coords2D[v1][0] / 2 * (width - 1);
    int y1 = coords2D[v1][1] / 2 * (height - 1);
    double z1 = coords2D[v1][2];

    int x2 = coords2D[v2][0] / 2 * (width - 1);
    int y2 = coords2D[v2][1] / 2 * (height - 1);
    double z2 = coords2D[v2][2];

    int minX = std::max(0, std::min(std::min(x0, x1), x2));
    int maxX = std::min(width - 1, std::max(std::max(x0, x1), x2));
    int minY = std::max(0, std::min(std::min(y0, y1), y2));
    int maxY = std::min(height - 1, std::max(std::max(y0, y1), y2));

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            double w0 = ((y1 - y2) * (x - x2) + (x2 - x1) * (y - y2)) /
                        ((y1 - y2) * (x0 - x2) + (x2 - x1) * (y0 - y2));
            double w1 = ((y2 - y0) * (x - x2) + (x0 - x2) * (y - y2)) /
                        ((y1 - y2) * (x0 - x2) + (x2 - x1) * (y0 - y2));
            double w2 = 1 - w0 - w1;

            if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
                double depth = w0 * z0 + w1 * z1 + w2 * z2;

                if (depth < depthBuffer[y][x]) {
                    depthBuffer[y][x] = depth;
                    screen[y][x] = "!";
                }
            }
        }
    }
}

void displayScreen() {
    // todo: implement ncurses for look better
    return;

}
