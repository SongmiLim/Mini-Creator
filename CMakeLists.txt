cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME mini_creator)
project(${PROJECT_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/3rdparty)

include(3rdparty)

# GLOB_RECURSE already descends into subdirectories, so each tree needs only
# one pattern. CONFIGURE_DEPENDS re-globs on build so new files are picked up
# without a manual CMake re-run.
file(GLOB_RECURSE COMMANDS_SRC CONFIGURE_DEPENDS "src/commands/*.cpp" "src/commands/*.h")
file(GLOB_RECURSE CORE_SRC CONFIGURE_DEPENDS "src/core/*.cpp" "src/core/*.h")
file(GLOB_RECURSE GRAPHICS_SRC CONFIGURE_DEPENDS "src/graphics/*.cpp" "src/graphics/*.h")
file(GLOB_RECURSE UI_SRC CONFIGURE_DEPENDS "src/ui/*.cpp" "src/ui/*.h")

qt_add_executable(${PROJECT_NAME}
    src/main.cpp
    src/app.h src/app.cpp
    ${COMMANDS_SRC}
    ${CORE_SRC}
    ${GRAPHICS_SRC}
    ${UI_SRC}
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LINK_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)