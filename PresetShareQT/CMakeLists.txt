cmake_minimum_required(VERSION 3.5)

project(PresetShareQT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets Core Gui Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Gui Network)

set(IMG_DIR ${CMAKE_SOURCE_DIR}/images)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

include_directories(${IMG_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

file(GLOB_RECURSE SOURCES
        ${IMG_DIR}/*.png
        ${INCLUDE_DIR}/*.h
        ${SOURCE_DIR}/*.cpp
        )

add_executable(PresetShareQT ${SOURCES})

target_include_directories(PresetShareQT PRIVATE ${INCLUDE_DIR})
target_include_directories(PresetShareQT PRIVATE ${SOURCE_DIR})
target_include_directories(PresetShareQT PRIVATE ${IMG_DIR})

target_link_libraries(PresetShareQT
        Qt5::Widgets
        Qt5::Core
        Qt5::Gui
        Qt5::Network)


install(TARGETS PresetShareQT DESTINATION .)
