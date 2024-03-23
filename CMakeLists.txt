cmake_minimum_required(VERSION 3.25)
project(EstimationBruteForce)

set(CMAKE_CXX_STANDARD 17)

add_executable(EstimationBruteForce main.cpp Cell.cpp Cell.h launcher.cpp launcher.h Incidence_func.cpp Incidence_func.h)