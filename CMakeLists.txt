cmake_minimum_required(VERSION 3.5)
project(XMbot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLOOX REQUIRED gloox)

include_directories(${GLOOX_INCLUDE_DIRS} src)

set(SOURCES
    src/main.cpp
    src/XMbotLogicRealiosation.cpp
    src/commandHandler.cpp
)

add_executable(XMbot ${SOURCES})

target_link_libraries(XMbot ${GLOOX_LIBRARIES})

