cmake_minimum_required(VERSION 3.10)

# set the project name and VERSION
project(Spell_Check VERSION 1.0)

# specify project directories
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(TEST_SRC_DIR ${PROJECT_SOURCE_DIR}/tests)

# the following 
inlcude_directories("${SRC_DIR}")

add_executable(spell_check ${SRC_DIR}/main.c)

#target_include_directories(Spell_Check PUBLIC ${PROJECT_BINARY_DIR})

