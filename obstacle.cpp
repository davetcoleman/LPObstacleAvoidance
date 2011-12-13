#include "obstacle.h"
#include "graphics.h" // For drawing stuff

void draw_lp(void){

	// Draw initial point
	coord initPoint;
	initPoint.x = 10; initPoint.y = 5; initPoint.z = 0;
	renderPoint(initPoint);

	// Draw final point
	coord finPoint;
	finPoint.x = 15; finPoint.y = 25; finPoint.z = 0;
	renderPoint(finPoint);	

	// Calc distance between two points to get number of needed points for program
	//int N = sqrt(finPoint.x - initPoint.x, 2) + pow(finPoint.y - initPoint.y, 2) );
	int N = abs(finPoint.x - initPoint.x) + abs(finPoint.y - initPoint.y);
	
	// Draw coordinates
	coord window[3];
	window[0].x = 100; window[0].y = 0; window[0].z = 0; // top left, clockwise
	window[1].x = 0; window[1].y = 0; window[1].z = 0;
	window[2].x = 0; window[2].y = 100; window[2].z = 0;
	renderPolygon(window, 3);

	// Max workspace
	coord max;
	max.x = 30; max.y = 30; max.z = 30;
	
	// Draw obstacle
	coord obstacle[4];
	obstacle[0].x = 10; obstacle[0].y = 10; obstacle[0].z = 0; // top left, clockwise
	obstacle[1].x = 20; obstacle[1].y = 10; obstacle[1].z = 0;
	obstacle[2].x = 20; obstacle[2].y = 20; obstacle[2].z = 0;
	obstacle[3].x = 10; obstacle[3].y = 20; obstacle[3].z = 0;
	//renderPolygonFilled(obstacle, 4);	

	// Output points to data file for GLPK
	ofstream data("data.dat");
	data << "data;\n\n";
	data << "param N := " << N << ";\n";
	
	printCoord(initPoint, "i", data);
	printCoord(finPoint, "f", data);
	printCoord(obstacle[0], "o1", data);
	printCoord(obstacle[1], "o2", data);
	printCoord(obstacle[2], "o3", data);
	printCoord(obstacle[3], "o4", data);
	printCoord(max, "m", data);
	
	
	data << "end;\n\n";
	data.close();

	// Run the GLPK ampl file and output results to screen
	remove("result.dat"); // delete old file first to prevent displaying when there is an error	
	FILE* pipe = popen("glpsol --math lp_problem2.ampl --data data.dat", "r");

	if (!pipe)
		cout << "ERROR";
	char buffer[128];
	while(!feof(pipe)) {
		if(fgets(buffer, 128, pipe) != NULL)
			cout << buffer;
	}
	pclose(pipe);
	cout << "\n ----------------------------------------------------------- \n";
	
	// Input results file for plotting
	ifstream result("result.dat");

	// Error Check
	if ( !result.is_open()) {
		cout << "Error opening results file. Probably glpk solver had error." << endl;
		exit(1);
	}

	// Input first number and check
	int check;
	result >> check;
	if(check != 999){
		cout << "Error in file format." << endl;
		exit(1);		
	}

	coord path[N+2];
	path[0] = initPoint;
	int i = 1;
	
	while(i < N + 1)
	{
		// Draw point
		coord point1;
		result >> point1.x >> point1.y;
		point1.z = 0;
		path[i] = point1;
		renderPoint(point1);
		debugPoint(point1);
		i++;
	}
	
	// Draw path
	path[i] = finPoint;
	renderPolygon(path, N+2);
	
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

