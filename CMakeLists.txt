cmake_minimum_required(VERSION 3.13)
project(facerec)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )
find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
add_executable(facerec main.cpp)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries( facerec ${OpenCV_LIBS} )
target_link_libraries(facerec ${GTK_LIBS})
target_link_libraries(facerec ${GTK3_LIBRARIES})