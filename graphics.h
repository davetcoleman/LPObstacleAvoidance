#include <glew.h> // Include the GLEW header file
#include <glut.h> // Include the GLUT header file
#include "obstacle.h"

void keyOperations (void);

void renderPolygonFilled (coord point[], size_t num_points);

void renderPolygon (coord point[], size_t num_points);

void renderPoint (coord point);

void display (void);

void reshape (int width, int height);

void keyPressed (unsigned char key, int x, int y);

void keyUp (unsigned char key, int x, int y);

void graphicsInit (int argc, char **argv);
