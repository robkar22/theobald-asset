cmake_minimum_required(VERSION 3.20)

project(theobald_asset LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(theobald-server
    src/main.cpp
    src/server.cpp
    src/http.cpp
    src/router.cpp
    src/database.cpp
)
find_package(SQLite3 REQUIRED)

target_include_directories(theobald-server PRIVATE include)
target_link_libraries(theobald-server PRIVATE SQLite3::SQLite3)

target_compile_options(theobald-server PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
