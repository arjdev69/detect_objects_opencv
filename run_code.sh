g++ -g -Wall -pedantic -std=c++11 marker_object.cpp -o marker `pkg-config --cflags --libs opencv`



./marker ./resources/video.avi