# Parameters ----------------------------------------------------------------

# Initial Point:
param xi; param yi; param zi;

# Final Point:
param xf; param yf; param zf;

# Obstacle Coordinates
param xo1; param yo1; param zo1;
param xo2; param yo2; param zo2;
param xo3; param yo3; param zo3;
param xo4; param yo4; param zo4;

# Workspace Constraints
param xm; param ym; param zm;

# Other Parameters ------------------------------------------------------------

param N default 4; # number of time steps / points
param NN := N -1;

set T := 1..N;	  # number of time steps / points
set TT := 1..NN;  # one less than number of time steps
set D := 1..2;    # 2 dimensions: x and y
set C := 1..4;    # number of manually created abs constraints

# Variables to Solve for -------------------------------------------------------

var points{t in T, d in D} >= 0;                        /* answer to problem */
var abs1{t in TT, d in D};
var abs2{c in C};

minimize distance: (sum{c in C} abs2[c]) + (sum{ t in TT, d in D } abs1[t,d]);

# Square obstacle
#s.t. obs

# Absolute Distance between midpoints
s.t. abs_min{t in TT, d in D}:  points[t+1,d] - points[t,d] - abs1[t,d] <= 0;
s.t. abs_max{t in TT, d in D}: -points[t+1,d] + points[t,d] - abs1[t,d] <= 0;

s.t. abs_diff{t in TT}: abs1[t,1] + abs1[t,2] >= 1;


#s.t. abs_max{t in TT, d in D}: abs1[t,d] <= 0;

# Initial X Axis
s.t. a1:  points[1,1] - xi - abs2[1] <= 0; 
s.t. a2: -points[1,1] + xi - abs2[1] <= 0; 

# Initial Y Axis
s.t. a3:  points[1,2] - yi - abs2[2] <= 0; 
s.t. a4: -points[1,2] + yi - abs2[2] <= 0; 

# Final X Axis
s.t. a5:  points[N,1] - xf - abs2[3] <= 0; 
s.t. a6: -points[N,1] + xf - abs2[3] <= 0; 

# Final Y Axis
s.t. a7:  points[N,2] - yf - abs2[4] <= 0; 
s.t. a8: -points[N,2] + yf - abs2[4] <= 0; 


#minimize dist: f(points[1,1],15) + points[2,1] - 5 + sum{d in D, t in T} points[t,d];   /* manhattan distance */

#s.t. piecewise{t in T}: <<1-AM,P1,3,5; -5, -1,0,1.5,3>> points[1,t];

#s.t. supply{d in D}: sum{j in T} x[i,j] <= a[i];	/* observe supply limit at plant d */

#s.t. demand{j in T}: sum{d in D} x[i,j] >= b[j];	/* satisfy demand at market j */

solve;
display points;


printf: "%d\n", 999 > "result.dat";
#printf{t in T, d in D} "%d,%d %.3f \n", t,d,points[t,d] >> "result.dat";
printf{t in T, d in D} "%.3f ", points[t,d] >> "result.dat";


#printf: "%.3f %.3f %.3f\n", x1, y1, z1 > "result.dat";
#printf: "%.3f %.3f %.3f\n", x2, y2, z2 >> "result.dat";
#printf: "%d %d\n", A, B >> "result.dat";


end;
