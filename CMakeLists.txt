cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 将include目录添加到编译的头文件搜索路径中
include_directories(${PROJECT_SOURCE_DIR}/include)

# 包含子目录
add_subdirectory(src)

# 指定可执行文件生成目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)