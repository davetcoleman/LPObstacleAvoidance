
# Parameters ---------------------------------------------------------

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


# Variables to Solve for ---------------------------------------------

var x1; var y1; var z1; # first point
var x2; var y2; var z2; # second point
var abs1; var abs2; var abs3; var abs4; var abs5; var abs6; # absolute values
var abs7; var abs8; var abs9; var abs10;  # absolute values
var A, binary; var B, binary; # path choices


# Problem -----------------------------------------------------------

minimize distance: abs1 + abs2 + abs3 + 2*abs4 + 2*abs5 + 2*abs6 + abs7 + abs8 + abs9;

# path choices
path: A + B = 1;

# x1
  l1: 0 *A  + xo2*B <= x1;  # x1 greater than
  h1: xo1*A + xm *B >= x1;  # x1 less than

  l2: 0              <= y1; 
  h2: yo1*A + yo2*B  >= y1;

  l3: 0 <= z1; h3: z1 <= zm;

# x2
  l4: 0  *A + xo3*B <= x2; 
  h4: xo4*A + xm *B >= x2;

  l5: yo4*A + xo3*B <= y2; 
  h5: ym            >= y2;

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
display x1, y1, z1, x2, y2, z2, A, B;  # print result

printf: "%.3f %.3f %.3f\n", x1, y1, z1 > "result.dat";
printf: "%.3f %.3f %.3f\n", x2, y2, z2 >> "result.dat";
printf: "%d %d\n", A, B >> "result.dat";

end;