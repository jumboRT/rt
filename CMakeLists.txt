cmake_minimum_required(VERSION 3.8)

if(MSVC)
	add_compile_options(/Wall)
else()
	add_compile_options(-Wall -Wextra -pedantic)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(rt VERSION 0.0.0 LANGUAGES CXX)

add_library(rt src/test/assert.cc)
target_include_directories(rt PUBLIC include)

add_executable(rt-bin src/main.cc)
target_link_libraries(rt-bin rt)
set_target_properties(rt-bin PROPERTIES OUTPUT_NAME rt)

add_executable(rt-test EXCLUDE_FROM_ALL src/test/main.cc src/test/tester.cc)
target_link_libraries(rt-test rt)

include(CTest)

function(rt_add_test name)
	add_test(rt-${name} rt-test ${name})
	set_tests_properties(rt-${name} PROPERTIES FIXTURES_REQUIRED rt-test)
endfunction()

add_test(rt-test "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --config "$<CONFIG>" --target rt-test)
set_tests_properties(rt-test PROPERTIES FIXTURES_SETUP rt-test)

rt_add_test(vector)
rt_add_test(matrix)
rt_add_test(quadratic)
