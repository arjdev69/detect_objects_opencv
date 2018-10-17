cmake_minimum_required(VERSION 2.8)
project( detect_objects )
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread -w")
find_package( OpenCV 3 REQUIRED )
INCLUDE_DIRECTORIES(
    include
    ${OpenCV_INCLUDE_DIRS}
    )
add_executable( detect_object src/main.cpp src/marker_object_implement.cpp )
target_link_libraries( detect_object ${OpenCV_LIBS} )