cmake_minimum_required(VERSION 3.0.0)
project(EntApp VERSION 1.0.0)

include(CTest)
enable_testing()

add_executable(EntApp main.cpp Book.cpp Games.cpp Screens.cpp connection.cpp server.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)