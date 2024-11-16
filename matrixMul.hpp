#pragma once
#include "helpers.hpp"
#include <cstdlib>
#include <iostream>

void applyRotation(double rotMatrix[3][3]);
void applyProjection(double vec[4], double projMatrix[4][4], double vec2d[3]);
void matrixMul3D(double matrix1[3][3], double matrix2[3][3], double ans[3][3]);
void project2D(double scaleFactor, double fov, double aspect, double far, double near, double coords2D[8][4]);
void offsetCube(int offset);
