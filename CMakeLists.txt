cmake_minimum_required(VERSION 3.5)

project(QEditor LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_subdirectory("${CMAKE_SOURCE_DIR}/deps/fmt")

# Adds the source files into the executable
add_executable(QEditor
  src/main.cpp
  src/Window/MainWindow.cpp
  src/Window/About.cpp
  src/Menu/FileMenu.cpp
  src/Menu/EditMenu.cpp
  src/Menu/HelpMenu.cpp
  src/Editor/Editor.cpp
  src/Highlighter.cpp
  src/LinkLabel.cpp
)

# The include directories
target_include_directories(QEditor PRIVATE
  ${CMAKE_SOURCE_DIR}/deps/fmt/include
)

# The library directories
target_link_directories(QEditor PRIVATE
  ${CMAKE_BINARY_DIR}/deps/fmt/
)

target_link_libraries(QEditor PRIVATE Qt5::Widgets fmt::fmt pthread stdc++fs)

if (CMAKE_BUILD_TYPE MATCHES Debug)
  message("-- Defining Debug macros!")
  target_compile_definitions(QEditor PRIVATE DEBUG ROOT_DIR="${CMAKE_SOURCE_DIR}")
else()
  message("-- Defining Release macros!")
  target_compile_definitions(QEditor PRIVATE RELEASE ROOT_DIR="${CMAKE_SOURCE_DIR}")
endif()
