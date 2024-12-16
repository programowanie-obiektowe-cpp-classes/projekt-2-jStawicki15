cmake_minimum_required(VERSION 3.14)
project(cpp-project CXX)

add_subdirectory(OpenXLSX)

file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(cpp-project ${SRC_FILES})

target_link_libraries(cpp-project OpenXLSX::OpenXLSX)

target_include_directories(cpp-project PUBLIC "${CMAKE_SOURCE_DIR}/include")
set_target_properties(cpp-project PROPERTIES CXX_STANDARD 23)
