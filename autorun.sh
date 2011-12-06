g++ obstacle.cpp graphics.cpp -I /usr/include/GL/ -L /usr/include/GL/ -lglut -lGL -lGLU -lGLEW -lX11 -lXmu -lXi -lm -o obstacle;
if [ $? -eq 0 ] ; then
    ./obstacle;
fi