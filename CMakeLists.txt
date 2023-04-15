cmake_minimum_required(VERSION 3.16)
project(VideoPlayer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(VideoPlayer
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

target_link_libraries(VideoPlayer PRIVATE Qt5::Widgets ${OpenCV_LIBS})
