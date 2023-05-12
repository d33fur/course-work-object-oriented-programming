cmake_minimum_required(VERSION 3.5)

if (WIN32)
project(PresetShareQT LANGUAGES CXX)
elseif(UNIX)
project(PresetShareQT)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
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
set(APP_ICON_RESOURCE_WINDOWS ${CMAKE_SOURCE_DIR}/icon.rc)

include_directories(${IMG_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})
include_directories(${APP_ICON_RESOURCE_WINDOWS})

file(GLOB_RECURSE SOURCES
        ${IMG_DIR}/*.qrc
        ${INCLUDE_DIR}/*.h
        ${SOURCE_DIR}/*.cpp
        ${APP_ICON_RESOURCE_WINDOWS})

if (WIN32)
add_executable(${PROJECT_NAME} WIN32 ${SOURCE_DIR}/main.cpp ${SOURCES})
elseif(UNIX)
add_executable(${PROJECT_NAME} ${SOURCES})
endif()

target_include_directories(PresetShareQT PRIVATE ${INCLUDE_DIR})
target_include_directories(PresetShareQT PRIVATE ${SOURCE_DIR})
target_include_directories(PresetShareQT PRIVATE ${IMG_DIR})

target_link_libraries(PresetShareQT
        Qt5::Widgets
        Qt5::Core
        Qt5::Gui
        Qt5::Network)

install(TARGETS PresetShareQT DESTINATION .)
