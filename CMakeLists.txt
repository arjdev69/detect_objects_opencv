cmake_minimum_required(VERSION 2.8)
project( detect_objects )
find_package( OpenCV 3 REQUIRED )
include(
    include
)
add_executable( detect_object src/main.cpp src/marker_object_implement.cpp )
target_link_libraries( detect_object ${OpenCV_LIBS} )