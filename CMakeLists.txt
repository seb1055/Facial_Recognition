cmake_minimum_required(VERSION 3.13)
project(Facial_Recognition)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )

add_executable(Facial_Recognition main.cpp FaceDetector.cpp FaceDetector.h Face.cpp Face.h)

target_link_libraries( Facial_Recognition ${OpenCV_LIBS} )
