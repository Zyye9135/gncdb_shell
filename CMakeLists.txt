cmake_minimum_required(VERSION 3.10)
project(gncdb_shell C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g -fdiagnostics-color=always")

# 包含头文件目录
include_directories(gncdblib/include)

# 查找所有源文件
file(GLOB SRC_FILES src/*.c)

# 添加可执行文件，避免与main.c冲突
add_executable(gncdb_shell ${SRC_FILES})

# 设置输出路径
set_target_properties(gncdb_shell PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# 链接静态库和系统库
add_library(gncdb STATIC IMPORTED)
set_target_properties(gncdb PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/gncdblib/lib/libgncdb.a)

target_link_libraries(gncdb_shell gncdb m readline)

include(InstallRequiredSystemLibraries)

# CPack配置
set(CPACK_PACKAGE_NAME "gncdb-shell")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "GNCDB Shell - A database shell tool")
set(CPACK_PACKAGE_VENDOR "Zyy")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_CONTACT "Zyy <zyye9135@mail.nwpu.edu.cn>")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Zyy <zyye9135@mail.nwpu.edu.cn>")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libreadline8")
set(CPACK_GENERATOR "DEB")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

# 安装目标
install(TARGETS gncdb_shell DESTINATION bin)
install(FILES README.md DESTINATION share/doc/gncdb-shell)
# 安装配置文件
install(FILES config.ini DESTINATION etc/gncdb-shell)
# 创建用户配置目录
install(CODE "execute_process(COMMAND mkdir -p \$ENV{HOME}/.gncdb)")
install(FILES config.ini DESTINATION $ENV{HOME}/.gncdb)
# 创建日志目录
install(DIRECTORY DESTINATION var/log/gncdb-shell)

include(CPack)