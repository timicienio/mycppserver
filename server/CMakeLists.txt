cmake_minimum_required(VERSION 3.10)
project(my_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# target_compile_features(${TARGET_NAME} cxx_std_17)

set(SOURCE_FILES src/main.cpp src/Server.cpp src/Server.h src/Connection.cpp src/Connection.h)

add_executable(my_server ${SOURCE_FILES})