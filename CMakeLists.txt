cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME mini_creator)
project(${PROJECT_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/3rdparty)

include(3rdparty)

file(GLOB_RECURSE COMMANDS_SRC "src/commands/*.cpp" "src/commands/*.h")
file(GLOB_RECURSE CORE_SRC "src/core/*.cpp" "src/core/*.h")
file(GLOB_RECURSE COMPONENTS_SRC "src/components/*.cpp" "src/components/*.h")
file(GLOB_RECURSE UI_SRC "src/ui/*.cpp" "src/ui/*.h" "src/ui/widgets/*.cpp" "src/ui/widgets/*.h"
"src/ui/menu_bar/*.cpp" "src/ui/menu_bar/*.h")

qt_add_executable(${PROJECT_NAME}
    src/main.cpp
    src/app.h src/app.cpp
    ${COMMANDS_SRC}
    ${CORE_SRC}
    ${COMPONENTS_SRC}
    ${UI_SRC}
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LINK_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)