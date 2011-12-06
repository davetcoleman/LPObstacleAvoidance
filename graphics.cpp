#include "graphics.h" // Header
#include "obstacle.h" // main program

bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)


void keyOperations (void) {
	if (keyStates[GLUT_KEY_LEFT]) { // If the left arrow key has been pressed
		// Perform left arrow key operations
	}
}

void renderPolygonFilled (coord point[], size_t num_points) {
   	glBegin(GL_QUADS); // Start drawing a quad primitive
	
	glColor3f(0.5f, 0.5f, 0.5f); // Grey

	for(size_t i = 0; i < num_points; i++)
	{
		glVertex3f(point[i].x, point[i].y, point[i].z); // point of polygon
	}
	
	glEnd();
}

void renderPolygon (coord point[], size_t num_points) {
	//	glBegin(GL_QUADS); // Start drawing a quad primitive
	glBegin(GL_LINE_STRIP); // Start drawing a line primitive
	
	glColor3f(0.5f, 0.5f, 0.5f); // Grey

	for(size_t i = 0; i < num_points; i++)
	{
		glVertex3f(point[i].x, point[i].y, point[i].z); // point of polygon
	}
	
	glEnd();
}

void renderPoint (coord point) {
	glPointSize(5.0f);
	glBegin(GL_POINTS); // Start drawing a point primitive

	glColor3f(0.0f, 0.0f, 1.0f); //black
	
	glVertex3f(point.x, point.y, point.z); // The bottom left corner

	glEnd();
}

void display (void) {
	keyOperations();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Clear the background of our window to black
	glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations

	glTranslatef(-15.0f, -15.0f, -40.0f); //Push eveything 5 units back into the scene, otherwise we won't see the primitive

	glColor3f(0.0f, 0.0f, 1.0f); //black	
	//	renderPoint(0.0f, 0.0f, 0.0f); // point	
	draw_lp();
	
	glFlush(); // Flush the OpenGL buffers to the window
}




void reshape (int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)

	// Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes	
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
	
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
}

void keyPressed (unsigned char key, int x, int y) {
	keyStates[key] = true; // Set the state of the current key to pressed
}

void keyUp (unsigned char key, int x, int y) {
	keyStates[key] = false; // Set the state of the current key to not pressed
}

void graphicsInit(int argc, char **argv) {

	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode (GLUT_SINGLE); // Set up a basic display buffer (only single buffered for now)
	glutInitWindowSize (1000, 900); // Set the width and height of the window
	glutInitWindowPosition (100, 100); // Set the position of the window
	glutCreateWindow ("LP Simulation"); // Set the title for the window

	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering

	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping

	glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses
	glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events

	glutMainLoop(); // Enter GLUT's main loop
}

