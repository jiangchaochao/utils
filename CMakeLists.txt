cmake_minimum_required(VERSION 3.15)
project(utils C)

set(CMAKE_C_STANDARD 99)

# 源文件
AUX_SOURCE_DIRECTORY(src SRC_LIST_SRC)
AUX_SOURCE_DIRECTORY(./ SRC_LIST)

# 头文件
INCLUDE_DIRECTORIES(inc INCLUDE_DIR)
LINK_DIRECTORIES(./ ${INCLUDE_DIR})
# 静态库
add_library(utils_static STATIC ${SRC_LIST_SRC} ${SRC_LIST})
# 动态库
add_library(utils SHARED ${SRC_LIST_SRC} ${SRC_LIST})

# 设置静态库的输出名称
set_target_properties(utils_static PROPERTIES OUTPUT_NAME "utils")
# 使动态库和静态库同时存在
set_target_properties(utils PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(utils_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# 指定动态库版本
# VERSION 动态库版本
# SOVERSION API版本
set_target_properties(utils PROPERTIES VERSION 1.0 SOVERSION 1)
# 将动态库与动态库同时安装到lib目录中
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/libs)


