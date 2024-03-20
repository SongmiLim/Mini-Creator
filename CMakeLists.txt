cmake_minimum_required(VERSION 3.13)

# Set the project name and C++ standard
set(PROJECT_NAME mini_creator)
set(CMAKE_CXX_STANDARD 17)

set(WINDOW_NAME "Mini Creator")
set(WINDOW_WIDTH 640)
set(WINDOW_HEIGHT 480)

# Declare the project
project(${PROJECT_NAME})
add_executable(${PROJECT_NAME}  
src/main.cpp
src/common.cpp src/common.h
src/shader.cpp src/shader.h
src/program.cpp src/program.h
src/context.cpp src/context.h
src/buffer.cpp src/buffer.h
src/vertex_layout.cpp src/vertex_layout.h)

include(Dependency.cmake)

# Add options for include / library directories
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})

#Link the libraries
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})

target_compile_definitions(${PROJECT_NAME} PUBLIC
WINDOW_NAME="${WINDOW_NAME}"
WINDOW_WIDTH=${WINDOW_WIDTH}
WINDOW_HEIGHT=${WINDOW_HEIGHT}
)

# Set up dependencies so that dependencies are built first
add_dependencies(${PROJECT_NAME} ${DEP_LIST})