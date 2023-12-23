cmake_minimum_required(VERSION 3.5)
project(monopoly VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
include_directories(include)
enable_testing()

add_executable(monopoly src/main.cpp src/player.cpp src/game.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
