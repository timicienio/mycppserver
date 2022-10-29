cmake_minimum_required(VERSION 3.10)
project(my_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# target_compile_features(${TARGET_NAME} cxx_std_17)

set(SOURCE_FILES src/main.cpp src/Client.cpp src/Client.h)

add_executable(my_client ${SOURCE_FILES})