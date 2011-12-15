#include "obstacle.h"
#include "graphics.h" // For drawing stuff

void draw_lp(void){

	// Draw initial point
	coord initPoint;
	initPoint.x = 10; initPoint.y = 5; initPoint.z = 0;
	
	// Draw final point
	coord finPoint;
	finPoint.x = 16; finPoint.y = 30; finPoint.z = 0;

	// Calc distance between two points to get number of needed points for program
	int N = 1.5*abs(finPoint.x - initPoint.x) + abs(finPoint.y - initPoint.y);
	
	// Draw coordinates
	coord window[3];
	window[0].x = 100; window[0].y = 0; window[0].z = 0; // top left, clockwise
	window[1].x = 0; window[1].y = 0; window[1].z = 0;
	window[2].x = 0; window[2].y = 100; window[2].z = 0;

	// Max workspace
	coord max;
	max.x = 30; max.y = 30; max.z = 30;
	
	// Draw polygon of E edges
	int E = 5;
	coord obstacle[E];
	obstacle[0].x = 10; obstacle[0].y = 15; obstacle[0].z = 0; // bottom left, counter clockwise
	obstacle[1].x = 20; obstacle[1].y = 10; obstacle[1].z = 0;
	obstacle[2].x = 25; obstacle[2].y = 15; obstacle[2].z = 0;
	obstacle[3].x = 20; obstacle[3].y = 20; obstacle[3].z = 0;
	obstacle[4].x = 10; obstacle[4].y = 18; obstacle[4].z = 0;	

   	renderPolygonFilled(obstacle, E);

	//return;
		
	// Output points to data file for GLPK
	ofstream data("data.dat");
	data << "data;\n\n";
	data << "param N := " << N << ";\n";
	data << "param E := " << E << ";\n";
	
	printCoord(initPoint, "i", data);
	printCoord(finPoint, "f", data);

	data << "param obst :   1   2  3 := \n";

	int x_max = 0;
	int x_min = 0;

	// First find the largest and smallest x and ensure the last x is not the same as the current one
	for(int i = 0; i < E; ++i)
	{
		// Check that two consequitive x's are not the same
		if(i == 0) { //check the last index
			if( obstacle[0].x == obstacle[E - 1].x ) { // they are same
				obstacle[0].x += .1; // add small amount
			}
		}else{
			if(obstacle[i].x == obstacle[i - 1].x){ // they are same
				obstacle[i].x += .1; // add small amount
			}
		}

		// Check for largest/smallest
		if(obstacle[x_max].x < obstacle[i].x)
			x_max = i;
		else if(obstacle[x_min].x > obstacle[i].x)
			x_min = i;

		cout << i << " " << obstacle[i].x << endl;
	}

	cout << " CHECK SEARCH " << x_max << " " << x_min << endl;

	double m; // slope
	double constraint; // y1 - m*x1
	int direction = -1; ; // up 1, down -1
	
	int index = x_min;
	coord temp1;
	coord temp2;
	// NOTE: array must be in order and counter-clockwise
	for(int i = 0; i < E; ++i)
	{
		cout << "Index: " << index << endl;
		
		temp1 = obstacle[index];

		// Now iterate
		if(index == E-1)
			index = 0;
		else
			index++;

		temp2 = obstacle[index];

		// Slope
		m = (temp2.y - temp1.y) / (temp2.x - temp1.x);
		// Constraint
		constraint = temp1.y - m * temp1.x;
			
		data << i+1 << " " << m << " " << constraint << " " << direction << endl;

		// Direction - flip if we've reached far right side
		if(i == x_max)
			direction = 1;
		
	}
	data << ";" << endl;

	
	data << "end;\n\n";
	data.close();

	//exit(1);
	
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

	
	// Draw initial stuff

	renderPoint(finPoint);	
	renderPoint(initPoint);
	renderPolygon(window, 3);
	
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
		//debugPoint(point1);
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

