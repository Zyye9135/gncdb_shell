cmake_minimum_required(VERSION 3.16)

project(gncdblib LANGUAGES CXX)

# 设置库的包含目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 链接现有的静态库
add_library(gncdb STATIC IMPORTED)
set_target_properties(gncdb PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libgncdb.a
)
