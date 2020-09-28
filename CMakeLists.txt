cmake_minimum_required(VERSION 3.15)
project(QueueProcessor CXX)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         ON) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       OFF)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

add_subdirectory(src)
add_subdirectory(tests)
