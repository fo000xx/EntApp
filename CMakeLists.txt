cmake_minimum_required(VERSION 3.28.4)
project(EntApp VERSION 2.0.0)

target_link_libraries(sqlite3 /usr/include/sqlite3.h)
add_executable(EntApp src/main.cpp src/databaseCommon.cpp)
