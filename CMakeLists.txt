cmake_minimum_required(VERSION 3.10)
project(observer_effect)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(observer_effect main.cpp)

target_link_libraries(observer_effect ${OpenCV_LIBS})
target_include_directories(observer_effect PRIVATE ${OpenCV_INCLUDE_DIRS})