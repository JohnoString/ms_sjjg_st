# CMakeList.txt: protobuf_test 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("protobuf_test")

add_compile_options(-std=c++11)

include_directories("E:\\private\\code\\protobuf-3.13.0\\src")

set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

add_definitions(-DUNICODE -D_UNICODE)
# 将源代码添加到此项目的可执行文件。
add_executable (protobuf_test "protobuf_test.cpp" "protobuf_test.h" "hello.pb.cc" "hello.pb.h")

#target_link_libraries(protobuf_test "E:\\private\\code\\protobuf_test\\bin\\protobuf-build\\Debug\\libprotoc.lib")
#target_link_libraries(protobuf_test "E:\\private\\code\\protobuf_test\\bin\\protobuf-build\\Debug\\libprotobuf.lib")
#target_link_libraries(protobuf_test "E:\\private\\code\\protobuf_test\\bin\\protobuf-build\\Debug\\libprotocd.lib")
#target_link_libraries(protobuf_test "E:\\private\\code\\protobuf_test\\bin\\protobuf-build\\Debug\\libcpmtd.lib")
#target_link_libraries(protobuf_test "E:\\private\\code\\protobuf_test\\bin\\protobuf-build\\Debug\\msvcprtd.lib")

target_link_libraries(protobuf_test "E:\\private\\code\\protobuf_test\\bin\\protobuf-build\\Debug\\libprotobuf-lited.lib")
target_link_libraries(protobuf_test "E:\\private\\code\\protobuf_test\\bin\\protobuf-build\\Debug\\libprotobufd.lib")
# TODO: 如有需要，请添加测试并安装目标。
