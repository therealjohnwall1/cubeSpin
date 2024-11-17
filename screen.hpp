#pragma once
#include <ncurses.h>
#include "helpers.hpp"

extern int edges[12][2];
extern int faces[6][4];

double** initBuffer(int width, int height);
void drawLine(int x0, int y0, int x1, int y1, std::string** screen, int height, int width);
void displayScreen();
void fillFace(int v0, int v1, int v2, int v3, int height, int width, double coords2D[8][4], std::string** screen, double** depthBuffer);
void fillTriangle(int v0, int v1, int v2, double coords2D[8][4], int height, int width, std::string** screen,double** depthBuffer);