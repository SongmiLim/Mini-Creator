cmake_minimum_required(VERSION 3.13)

# Set the project name and C++ standard
set(PROJECT_NAME mini_creator)
set(CMAKE_CXX_STANDARD 17)

# Declare the project
project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} src/main.cpp)

include(Dependency.cmake)

# Add options for include / library directories
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})

#Link the libraries
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})

# Set up dependencies so that dependencies are built first
add_dependencies(${PROJECT_NAME} ${DEP_LIST})