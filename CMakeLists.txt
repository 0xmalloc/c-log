cmake_minimum_required(VERSION 3.9)
project(c-log)

include_directories(include)
add_library(clog STATIC src/log.cpp)
