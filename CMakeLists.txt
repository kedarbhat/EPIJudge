cmake_minimum_required(VERSION 3.12)
project(EPIJudge CXX)

set(CMAKE_CXX_STANDARD 14)

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -wd4018 -wd4244 -wd4800 -wd4805)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wno-unused-variable -Wno-sign-compare")
    link_libraries(pthread)
endif()

add_subdirectory(epi_judge_cpp)
