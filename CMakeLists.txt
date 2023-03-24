cmake_minimum_required(VERSION 3.8)

if(MSVC)
	add_compile_options(/Wall)
else()
	add_compile_options(-Wall -Wextra -pedantic)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND RT_SRC src/test/assert.cc)

list(APPEND RT_TEST test/math/vector.cc)
list(APPEND RT_TEST test/math/matrix.cc)
list(APPEND RT_TEST test/math/quadratic.cc)

create_test_sourcelist(RT_TEST_SRC test.cc ${RT_TEST})

project(rt VERSION 0.0.0 LANGUAGES CXX)

add_library(rt-base STATIC ${RT_SRC})
target_include_directories(rt-base PUBLIC include)
add_executable(rt src/main.cc)
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
