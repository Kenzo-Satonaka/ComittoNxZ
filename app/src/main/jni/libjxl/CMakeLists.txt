# libjxl/CMakeLists.txt
cmake_minimum_required(VERSION 3.18.1)

# project()の前に設定オプションを宣言
option(BUILD_TESTING "Build libjxl tests" OFF)
option(JPEGXL_ENABLE_BENCHMARK "Build benchmark tools" OFF)
option(JPEGXL_ENABLE_EXAMPLES "Build examples" OFF)
option(JPEGXL_ENABLE_MANPAGES "Build man pages" OFF)
option(JPEGXL_ENABLE_TOOLS "Build tools" OFF)
option(JPEGXL_ENABLE_SKCMS "Build with skcms" OFF)

# 言語指定なしで宣言（親のCMakeLists.txtのC++環境を使用）
project(libjxl NONE)

# 必須依存関係（Android NDK内蔵のzlib）
find_package(ZLIB REQUIRED)

# third_party/highway の追加（存在確認付き）
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/third_party/highway/CMakeLists.txt")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/third_party/highway" "${CMAKE_CURRENT_BINARY_DIR}/third_party/highway")
endif()

# third_party/brotli の追加（存在確認付き）
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/third_party/brotli/CMakeLists.txt")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/third_party/brotli" "${CMAKE_CURRENT_BINARY_DIR}/third_party/brotli")
endif()

# JXL コアライブラリの追加（存在確認付き）
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/CMakeLists.txt")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib" "${CMAKE_CURRENT_BINARY_DIR}/lib")
endif()