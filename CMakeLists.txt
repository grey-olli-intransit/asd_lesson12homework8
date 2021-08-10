cmake_minimum_required(VERSION 2.8)
add_compile_options(-Wall -g)
project(l12hw8)
add_executable(l12hw8 src/l12hw8.c)
target_include_directories(l12hw8 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
#target_link_libraries(l12hw8 PRIVATE m)

