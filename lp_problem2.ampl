# Other Parameters ------------------------------------------------------------

param N default 4; # number of time steps / points
param NN := N - 1;
param M := 1000; # arbitrary large positive number
param m := 0.001; # arbitrary small number to prevent division by zero
param E default 4; # number of edges in polygon

set T := 1..N;	  # number of time steps / points
set TT := 1..NN;  # one less than number of time steps
set Dims := 1..2;    # 2 dimensions: x and y
set C := 1..4;    # number of manually created abs constraints
set Edges := 1..E; # number of total edges in polygons
set ConstData :=1..3; # slope, constraint, direction

# Input Parameters ----------------------------------------------------------------

# Initial Point:
param xi; param yi; param zi;

# Final Point:
param xf; param yf; param zf;

# Obstacle Description - edges x 3 data
param obst{e in Edges, c in ConstData};


# Variables to Solve for -------------------------------------------------------

var points{t in T, d in Dims} >= 0;  # set of x,y points for problem solution
var abs1{t in TT, d in Dims};        # middle steps
var abs2{c in C};                 # initial and final steps
var abs3{t in TT};                # optimize for hypotenues
#var abs4{c in C};                 # limit distance in initial and final steps
var orer{t in T, e in Edges}  binary; # vars used for doing ORs

# Objective Function -----------------------------------------------------------
minimize distance: sum{t in TT, d in Dims} abs1[t,d] +      # all constraints between initial and final
	           sum{c in C} abs2[c] +                 # initial and final point constraints
                   .5*sum{t in TT} abs3[t];                 # optimize hypotenus

# Constraints ------------------------------------------------------------------

# ABS Distance between midpoints
s.t. abs_min{t in TT, d in Dims}:  points[t+1,d] - points[t,d] - abs1[t,d] <= 0;
s.t. abs_max{t in TT, d in Dims}: -points[t+1,d] + points[t,d] - abs1[t,d] <= 0;

# Point to point distance limiter - more than .5 less than 2
s.t. abs_diff1{t in TT}: abs1[t,1] + abs1[t,2] >= .5;
s.t. abs_diff2{t in TT}: abs1[t,1] + abs1[t,2] <= 1;

# Point to point distance limiter for init and end
s.t. abs_diff3: abs2[1] + abs2[2] <= 8;
s.t. abs_diff4: abs2[3] + abs2[4] <= 7;

# ABS Distance Between change in x and y per point - optimize to hypotenus
s.t. abs_diff5{t in TT}:  abs1[t,1] - abs1[t,2] - abs3[t] <= 0;
s.t. abs_diff6{t in TT}: -abs1[t,1] + abs1[t,2] - abs3[t] <= 0;

# Obstacle Constraints - Square
#                                  direction* slope   * x         -direction* y          <= -direction*constraint+ OR
s.t. obstAll{t in TT, e in Edges}: obst[e,3]*obst[e,1]*points[t,1]-obst[e,3]*points[t,2] <= -obst[e,3]*obst[e,2] + M*orer[t,e];

#.t. obst1{t in TT}:  -m4*points[t,1] + points[t,2] <=  (yo1-m4*xo1) + M*orer[t,3]; # x_min
#s.t. obst3{t in TT}:  -m1*points[t,1] + points[t,2] <=  (yo1-m1*xo1) + M*orer[t,3]; # y_min
#s.t. obst4{t in TT}:   m3*points[t,1] - points[t,2] <= -(yo3-m3*xo3) + M*orer[t,4]; # y_max

#s.t. obst1{t in TT}:  points[t,1] <=  xo1 + M*orer[t,1]; # x_min
#s.t. obst2{t in TT}: -points[t,1] <= -xo2 + M*orer[t,2]; # x_max
#s.t. obst3{t in TT}:  points[t,2] <=  yo1 + M*orer[t,3]; # y_min
#s.t. obst4{t in TT}: -points[t,2] <= -yo3 + M*orer[t,4]; # y_max
s.t. obstOR{t in TT}: sum{e in Edges} orer[t,e] <= E-1; # at least one must be true

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

# Solve -----------------------------------------------------------------------

solve;
#display m1, m2, m3, m4;


printf: "%d\n", 999 > "result.dat";
#printf{t in T, d in D} "%d,%d %.3f \n", t,d,points[t,d] >> "result.dat";
printf{t in T, d in Dims} "%.3f ", points[t,d] >> "result.dat";


#printf: "%.3f %.3f %.3f\n", x1, y1, z1 > "result.dat";
#printf: "%.3f %.3f %.3f\n", x2, y2, z2 >> "result.dat";
#printf: "%d %d\n", A, B >> "result.dat";


end;
