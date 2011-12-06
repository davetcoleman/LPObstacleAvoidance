#include "obstacle.h"
#include "graphics.h" // For drawing stuff

void draw_lp(void){

	// Draw initial point
	coord initPoint;
	initPoint.x = 20; initPoint.y = 5; initPoint.z = 0;
	renderPoint(initPoint);

	// Draw final point
	coord finPoint;
	finPoint.x = 15; finPoint.y = 25; finPoint.z = 0;
	renderPoint(finPoint);	

	// Draw coordinates
	coord window[3];
	window[0].x = 100; window[0].y = 0; window[0].z = 0; // top left, clockwise
	window[1].x = 0; window[1].y = 0; window[1].z = 0;
	window[2].x = 0; window[2].y = 100; window[2].z = 0;
	renderPolygon(window, 3);

	// Draw obstacle
	coord obstacle[4];
	obstacle[0].x = 10; obstacle[0].y = 10; obstacle[0].z = 0; // top left, clockwise
	obstacle[1].x = 20; obstacle[1].y = 10; obstacle[1].z = 0;
	obstacle[2].x = 20; obstacle[2].y = 20; obstacle[2].z = 0;
	obstacle[3].x = 10; obstacle[3].y = 20; obstacle[3].z = 0;
	renderPolygonFilled(obstacle, 4);	

	// Output points to data file for GLPK
	ofstream data("data.dat");
	data << "data;\n\n";
	printCoord(initPoint, "i", data);
	printCoord(finPoint, "f", data);	
	data << "end;\n\n";
	data.close();

	// Run the GLPK ampl file and output results to screen
	FILE* pipe = popen("glpsol --math lp_problem.ampl --data data.dat", "r");
	if (!pipe)
		cout << "ERROR";
	char buffer[128];
	while(!feof(pipe)) {
		if(fgets(buffer, 128, pipe) != NULL)
			cout << buffer;
	}
	pclose(pipe);

	// Input results file for plotting
	ifstream result("result.dat");

	// Draw point 1
	coord point1;
	result >> point1.x >> point1.y >> point1.z;
	renderPoint(point1);
	debugPoint(point1);
	
	// Draw point 2
	coord point2;
	result >> point2.x >> point2.y >> point2.z;
	renderPoint(point2);
	debugPoint(point2);

	// Draw path
	coord path[4] = { initPoint, point1, point2, finPoint };
	renderPolygon(path, 4);

}

void debugPoint(coord point)
{
	cout << "Coordinate: " << point.x << " " << point.y << " " << point.z << endl;
}

void printCoord(coord point, const char* postName, ofstream &data)
{
	data <<  "param x" << postName << " := " << point.x <<"; \n";
	data <<  "param y" << postName << " := " << point.y <<"; \n";
	data <<  "param z" << postName << " := " << point.z <<"; \n";	
}

int main (int argc, char **argv) {

	// Start the OpenGL stuff
	graphicsInit(argc, argv);

	return 0;
}

