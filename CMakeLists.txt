cmake_minimum_required(VERSION 3.16)

project(Chessly)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Qt6 requires Automoc, Autouic and Autorcc to handle it's custom c++ extensions
set(CMAKE_AUTOMOC ON) # for detecting Q_OBJECT
set(CMAKE_AUTOUIC ON) # for converting .ui files to C++ headers (even if i'm not using it , it's a standard practice to enable it)
set(CMAKE_AUTORCC ON) # for locating Resources like(Icons, Images, Sounds)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Chessly
    src/main.cpp

    src/MainWindow.h
    src/MainWindow.cpp

    src/ChessBoard.h
    src/ChessBoard.cpp

    src/GameLogic.h
    src/GameLogic.cpp

    resources.qrc
)

target_link_libraries(Chessly PRIVATE Qt6::Widgets)

target_include_directories(Chessly PRIVATE src)

