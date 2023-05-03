cmake_minimum_required(VERSION 3.16)
project(VideoPlayerCV)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(Qt6_DIR "C:/Qt/6.5.0/mingw64/bin")
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories("C:/msys64/mingw64/include/opencv4")

#set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/msvc2019_64/bin")
#set(CMAKE_PREFIX_PATH "C:/Qt/6.5.0/mingw64/bin" "C:/msys64_20230318/mingw64/lib/cmake")
#set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64/lib/cmake")
#set(CMAKE_PREFIX_PATH "C:/Qt/6.5.0/mingw_64/lib/cmake")
#set(CMAKE_PREFIX_PATH "C:/Qt/6.5.0/mingw64/bin" )
#set(CMAKE_PREFIX_PATH "C:/msys64_20230318/mingw64/lib/cmake")
set(CMAKE_PREFIX_PATH "C:/Qt/6.5.0/mingw64/bin" "C:/msys64/mingw64/lib/cmake")

#find_package(Qt6 COMPONENTS Widgets REQUIRED)

#set(OpenCV_DIR "C:/opencv-4.x/cmake-build-debug")
set(OpenCV_DIR "C:/msys64/mingw64")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


#set(CMAKE_PREFIX_PATH "C:/Qt/6.5.0/mingw_64")
#find_package(OpenCV REQUIRED)

#find_package(OpenCV REQUIRED)
#find_package(Qt6 COMPONENTS Widgets REQUIRED)
#find_package(Qt5 COMPONENTS Widgets REQUIRED)


#set(OpenCV_INCLUDE_DIRS C:/opencv/build/include)

#include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(VideoPlayerCV
    main.cpp
    mainwindow.cpp
    mainwindow.h
)
#if(WIN32)
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#endif()
if (MSVC)
    add_compile_options(-Zc:__cplusplus -permissive-)
endif()

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
endif()
#target_link_libraries(VideoPlayerCV PRIVATE Qt5::Widgets ${OpenCV_LIBS})
target_link_libraries(VideoPlayerCV PRIVATE Qt6::Widgets ${OpenCV_LIBS})

#if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#    add_compile_options(/Zc:__cplusplus-) # Disable -Zc:__cplusplus
#endif()
#if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#    add_compile_options(/Zc:__cplusplus-) # Disable -Zc:__cplusplus
#    add_compile_options(/permissive-)    # Disable -permissive-
#    add_compile_options(/fpermissive)    # Use -fpermissive instead
#endif()
