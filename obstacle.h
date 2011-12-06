#pragma once

#include <glew.h> // Include the GLEW header file
#include <glut.h> // Include the GLUT header file
#include <iostream> // for saving to file
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

struct coord {
	float x;
	float y;
	float z;
};


void printCoord(coord point, const char* postName, ofstream &data);

void debugPoint(coord point);
	
void draw_lp(void);

int main (int argc, char **argv);

