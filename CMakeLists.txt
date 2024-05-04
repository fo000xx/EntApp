cmake_minimum_required(VERSION 3.29.2)
project(EntApp VERSION 2.0.0)

find_package(unofficial-sqlite3 CONFIG REQUIRED)

add_executable(EntApp src/main.cpp src/databaseCommon.cpp)
target_link_libraries(EntApp PRIVATE unofficial::sqlite3::sqlite3)
