cmake_minimum_required(VERSION 3.13)
project(Greeter_OpenFace)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )

add_executable(Greeter_OpenFace main.cpp FaceDetector.cpp FaceDetector.h Face.cpp Face.h)

target_link_libraries( Greeter_OpenFace ${OpenCV_LIBS} )
