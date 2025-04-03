# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(silverwing_simulator CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES src/silverwing_simulator.cpp)

# set(HEADERS ./header.h )

add_executable(silverwing_simulator ${SOURCES})

add_library(silverwing_simulator_lib SHARED ${SOURCES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(COMMON_COMPILE_OPTIONS -g -Wall -Wextra -Werror -O0)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(COMMON_COMPILE_OPTIONS -O3)
endif()

target_compile_options(silverwing_simulator PRIVATE ${COMMON_COMPILE_OPTIONS})
target_compile_options(silverwing_simulator_lib
                       PRIVATE ${COMMON_COMPILE_OPTIONS})

set_target_properties(silverwing_simulator PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                      ${CMAKE_BINARY_DIR})

set_target_properties(
  silverwing_simulator_lib
  PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set_target_properties(silverwing_simulator PROPERTIES VERSION )

# target_include_directories(silverwing_simulator PRIVATE src)
