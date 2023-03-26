cmake_minimum_required(VERSION 3.18)

if(MSVC)
	add_compile_options(/Wall)
else()
	add_compile_options(-Wall -Wextra) # -pedantic
endif()

project(rt VERSION 0.0.0 LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CUDA_STANDARD 11)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_EXTENSIONS OFF)
set(CMAKE_CUDA_ARCHITECTURES OFF)
set(CMAKE_CUDA_SEPARABLE_COMPILATION ON)

list(APPEND RT_BASE src/test/assert.cc)
list(APPEND RT_BASE src/shape/sphere.cc)

list(APPEND RT_SRC src/main.cu)

list(APPEND RT_TEST test/math/vector.cc)
list(APPEND RT_TEST test/math/matrix.cc)
list(APPEND RT_TEST test/math/quadratic.cc)
list(APPEND RT_TEST test/shape/sphere.cc)

set_source_files_properties(${RT_SRC} ${RT_BASE} ${RT_TEST} PROPERTIES LANGUAGE CUDA)
create_test_sourcelist(RT_TEST_SRC test.cc ${RT_TEST})

add_library(rt-base STATIC ${RT_BASE})
target_include_directories(rt-base PUBLIC include)
add_executable(rt ${RT_SRC})
target_link_libraries(rt rt-base)
add_executable(rt-test EXCLUDE_FROM_ALL ${RT_TEST_SRC})
target_link_libraries(rt-test rt-base)

include(CTest)

add_test(build "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --config "$<CONFIG>" --target rt-test)
set_tests_properties(build PROPERTIES FIXTURES_SETUP build)

foreach(test ${RT_TEST})
	string(REGEX MATCH "^([^/]*/)*[^.]+" name ${test})
	add_test(${name} rt-test ${name})
	set_tests_properties(${name} PROPERTIES FIXTURES_REQUIRED build)
endforeach()
