# INSTALL OPENCV 3.1.0

g++ -g -Wall -pedantic -std=c++11 marker_object.cpp -o markerOutput `pkg-config --cflags --libs opencv`

./markerOutput