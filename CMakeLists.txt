cmake_minimum_required(VERSION 3.24.2)
project(testproj CXX)

add_library(candle candle.h candle.cpp)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} candle)