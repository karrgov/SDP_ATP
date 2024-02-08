cmake_minimum_required(VERSION 3.0)

project(SDP_ATP)

set(CMAKE_CXX_STANDARD 20) 

set(SOURCES
    src/ProgramMain.cpp
    src/Tree.cpp
)

set(HEADERS
    include/Tree.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})