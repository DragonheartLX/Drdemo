# 最低cmake版本
cmake_minimum_required(VERSION 3.10)

# MSVC设置: 以utf8编译
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# C++ 标准：17+
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 声明C++项目
project(RayTracing LANGUAGES CXX)

# 寻找库的头文件
set(DEMO_HEADER_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../external/
)

# 添加src目录下所有源文件（每次新增文件不要修改cmake，只需重新执行cmake命令）
file(GLOB DEMO_SOURCE_PATH 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/**/*.h
)

# 添加编译目标
add_executable(RayTracing ${DEMO_SOURCE_PATH})

# 引入全部头文件路径
target_include_directories(RayTracing PUBLIC 
    ${DEMO_HEADER_PATH}
)

#依赖库
find_package(Threads)
    target_link_libraries(RayTracing ${CMAKE_THREAD_LIBS_INIT})