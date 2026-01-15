cmake_minimum_required(VERSION 3.16)

project(Chessly VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Qt6 requirs Automoc , Autouic and Autorcc to handle it's c++ extentions
set(CMAKE_AUTOMOC ON)# for detecting Q_OBJECT macros
set(CMAKE_AUTOUIC ON)# for converting .ui files to c++ headers (even tho i'm not using it , it's a standard parctice to enable it)
set(CMAKE_AUTORCC ON)# for locating resources like (Icons , Images , Sounds)

find_Package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Chessly
        src/main.cpp
        
        src/MainWindow.h
        src/MainWindow.cpp

        src/GameLogic.h
        src/GameLogic.cpp

        src/ChessBoard.h
        src/ChessBoard.cpp

        resources.qrc
)

target_link_libraries(Chessly PRIVATE Qt6::Widgets)

target_include_directories(Chessly PRIVATE src)