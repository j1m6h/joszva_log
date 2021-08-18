cmake_minimum_required(VERSION 3.5)

project(joszva_log)

add_library(${PROJECT_NAME} SHARED
    src/logger.cpp)