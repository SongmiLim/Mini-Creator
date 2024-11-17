cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME mini_creator)
project(${PROJECT_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/3rdparty)

include(3rdparty)

qt_add_executable(${PROJECT_NAME}  
    src/main.cpp
    src/app.h src/app.cpp
    src/ui/main_window.h src/ui/main_window.cpp
    src/ui/menu_bar.h src/ui/menu_bar.cpp
    src/ui/tool_bar.h src/ui/tool_bar.cpp
    src/ui/menu_bar/file_menu.h src/ui/menu_bar/file_menu.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LINK_LIBS})