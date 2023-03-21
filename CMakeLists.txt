
cmake_minimum_required(VERSION 3.23)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_executable(project main.cpp data_structures/Graph.cpp data_structures/Graph.h data_structures/VertexEdge.cpp data_structures/VertexEdge.h src/TrainManager.cpp src/TrainManager.h src/Station.h src/Network.cpp src/Network.h src/Station.cpp)