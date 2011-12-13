# Discrete time steps
param N;

# 2d coordinate matrix of size NxN
var x{ i in N, j in N };

minimize tester: sum{i in N} x[i] - x[i+1];

solve;

display x;

end;


data;

param N := 10;

end;