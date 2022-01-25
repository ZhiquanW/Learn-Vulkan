cmake_minimum_required(VERSION 3.13)
project(triangle)

set(CMAKE_CXX_STANDARD 17)
find_package(Vulkan REQUIRED)
include_directories(src/includes)
aux_source_directory(src  source_files)

add_executable(${PROJECT_NAME} ${source_files} src/main.cpp )
target_link_libraries(${PROJECT_NAME} glfw Vulkan::Vulkan)
