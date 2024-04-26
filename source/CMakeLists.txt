cmake_minimum_required(VERSION 3.8)
project(TextDoc)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin)

add_subdirectory(TextDocument)
add_subdirectory(Example)

set_property(TARGET Example PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin/${CMAKE_CFG_INTDIR})
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Example)
add_dependencies(Example TextDocument)
