cmake_minimum_required(VERSION 3.13)
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

set(CMAKE_CXX_STANDARD 17)
find_package(Vulkan REQUIRED)

aux_source_directory(src  source_files)

add_executable(${PROJECT_NAME} ${source_files}  )
target_link_libraries(${PROJECT_NAME} glfw3 Xi X11 pthread dl  Vulkan::Vulkan)
