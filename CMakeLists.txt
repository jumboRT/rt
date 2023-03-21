cmake_minimum_required(VERSION 3.8)

if(MSVC)
	add_compile_options(/Wall)
else()
	add_compile_options(-Wall -Wextra -pedantic)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(rt VERSION 0.0.0 LANGUAGES CXX)
add_executable(rt src/main.cc)
target_include_directories(rt PRIVATE include)
