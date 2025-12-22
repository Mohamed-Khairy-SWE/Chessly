cmake_minimum_required(VERSION 3.16)

project(Chessly)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Qt6 requires Automoc, Autouic and Autorcc to handle it's custom c++ extensions
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Chessly
    src/main.cpp

    src/MainWindow.h
    src/MainWindow.cpp
    
)

target_link_libraries(Chessly PRIVATE Qt6::Widgets)

target_include_directories(Chessly PRIVATE src)

