
# Initial Point:
param xi; param yi; param zi;

# Final Point:
param xf; param yf; param zf;

# Obstacle
var xo1 = 10; var yo1 = 10; var zo1 = 10; # coordinate of obstacle
var xo2 = 20; var yo2 = 10; var zo2 = 10; # coordinate of obstacle
var xo3 = 20; var yo3 = 20; var zo3 = 10; # coordinate of obstacle
var xo4 = 10; var yo4 = 20; var zo4 = 10; # coordinate of obstacle

# Workspace
var xm  = 30;  var ym  = 30; var zm  = 30; # physical constraints

# Variables to Solve for:
var x1; var y1; var z1;
var x2; var y2; var z2;
var abs1; var abs2; var abs3; var abs4; var abs5; var abs6;
var abs7; var abs8; var abs9; var abs10; #var abs11; var abs12;
#var abs13; var abs14; var abs15; var abs16; var abs17; var abs 18;

minimize distance: abs1 + abs2 + abs3 + 2*abs4 + 2*abs5 + 2*abs6 + abs7 + abs8 + abs9;

# x1
l1: 0 <= x1; h1: x1 <= xo1;
l2: 0 <= y1; h2: y1 <= yo1;
l3: 0 <= z1; h3: z1 <= zm;

# x2
l4: 0 <= x2; h4: x2 <= xo4;
l5: yo4 <= y2; h5: y2 <= ym;
l6: 0 <= z2; h6: z2 <= zm;

# Distance 1
a1:  x1 - xi - abs1 <= 0; # | x1 - xi |
a2: -x1 + xi - abs1 <= 0;
a3:  y1 - yi - abs2 <= 0; # | y1 - yi |
a4: -y1 + yi - abs2 <= 0;
a5:  z1 - zi - abs3 <= 0; # | z1 - zi |
a6: -z1 + zi - abs3 <= 0;

# Distance 2
a7:   x2 - x1 - abs4 <= 0; # | x2 - x1 |
a8:  -x2 + x1 - abs4 <= 0;
a9:   y2 - y1 - abs5 <= 0; # | y2 - y1 |
a10: -y2 + y1 - abs5 <= 0;
a11:  z2 - z1 - abs6 <= 0; # | z2 - z1 |
a12: -z2 + z1 - abs6 <= 0;

# Distance 3
a13:  xf - x2 - abs7 <= 0; # | xf - x2 |
a14: -xf + x2 - abs7 <= 0;
a15:  yf - y2 - abs8 <= 0; # | yf - y2 |
a16: -yf + y2 - abs8 <= 0;
a17:  zf - z2 - abs9 <= 0; # | zf - z2 |
a18: -zf + z2 - abs9 <= 0;


solve; # directive to solve
display x1, y1, z1, x2, y2, z2;  # print result

printf: "%.3f %.3f %.3f\n", x1, y1, z1 > "result.dat";
printf: "%.3f %.3f %.3f\n", x2, y2, z2 >> "result.dat";

end;