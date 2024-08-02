cmake_minimum_required(VERSION 3.5)
project(game)

file(GLOB_RECURSE PROJECT_SOURCES *.cpp *.h)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})