cmake_minimum_required(VERSION 3.8)
project(Example)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/../TextDocument/public)
link_libraries(TextDocument.lib)
link_directories($(PROJECT_SOURCE_DIR)/../../bin)

add_executable(Example main.cpp)
