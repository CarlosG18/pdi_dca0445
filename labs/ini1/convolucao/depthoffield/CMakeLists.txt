cmake_minimum_required(VERSION 3.0.0)
project(depthoffield VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenCV REQUIRED core imgproc highgui)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(depthoffield depthoffield.cpp)
target_link_libraries(depthoffield ${OpenCV_LIBS})