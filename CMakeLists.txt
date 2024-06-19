cmake_minimum_required(VERSION 3.29)
project(cxx-eda)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_executable(${PROJECT_NAME}
    src/main.cpp
)