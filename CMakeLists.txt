cmake_minimum_required(VERSION 3.10)
project(EmbeddedVisionSystem)

find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 11)

# Automatically handle Qt's MOC, RCC, and UIC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
    main.cpp
    mainwindow.cpp
    face_detector.cpp
)

set(HEADERS
    mainwindow.h
    face_detector.h
)

qt5_wrap_cpp(MOC_SRC mainwindow.h)

add_executable(EmbeddedVisionSystem
    ${SOURCES}
    ${HEADERS}
    ${MOC_SRC}
)

target_link_libraries(EmbeddedVisionSystem
    Qt5::Widgets
    ${OpenCV_LIBS}
)
