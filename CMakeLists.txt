cmake_minimum_required(VERSION 3.23)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_executable(project main.cpp src/Graph.cpp src/Graph.h src/VertexEdge.cpp src/VertexEdge.h)
