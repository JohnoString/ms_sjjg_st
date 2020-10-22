# CMakeList.txt: gtest_test 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("gtest_test")

add_compile_options(-std=c++11)

include_directories("E:\\private\\code\\googletest-master\\googletest\\include\\")

set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

add_definitions(-DUNICODE -D_UNICODE)

# 将源代码添加到此项目的可执行文件。
add_executable (gtest_test "gtest_test.cpp" "gtest_test.h")

target_link_libraries(gtest_test "E:\\private\\code\\googletest-master\\out\\build\\x86-Debug\\lib\\gtestd.lib")
# TODO: 如有需要，请添加测试并安装目标。
