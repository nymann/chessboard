cmake_minimum_required(VERSION 3.3)
project(chessboard)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(SOURCE_FILES chessboard.c)
add_executable(chessboard ${SOURCE_FILES})