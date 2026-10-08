cmake_minimum_required(VERSION 3.18.1)

project("comitton")

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------------------------
# 1. 依存ライブラリの追加 (libjxl & libavif)
# ------------------------------------------------------------------------------
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libjxl/CMakeLists.txt")
    add_subdirectory(libjxl)
endif()

# libavif の不要機能フラグ設定
set(AVIF_CODEC_DAV1D OFF CACHE BOOL "" FORCE)
set(AVIF_CODEC_AOM OFF CACHE BOOL "" FORCE)
set(AVIF_BUILD_APPS OFF CACHE BOOL "" FORCE)
set(AVIF_BUILD_TESTS OFF CACHE BOOL "" FORCE)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libavif/CMakeLists.txt")
    add_subdirectory(libavif)
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/avif/CMakeLists.txt")
    add_subdirectory(avif)
endif()

# ------------------------------------------------------------------------------
# 2. メインライブラリ "comitton" の定義
# ------------------------------------------------------------------------------
file(GLOB_RECURSE COMITTON_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

# 依存ライブラリ内部ソースの重複ビルドを防止
list(FILTER COMITTON_SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/libjxl/.*")
list(FILTER COMITTON_SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/libavif/.*")
list(FILTER COMITTON_SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/avif/.*")

add_library(
    comitton
    SHARED
    ${COMITTON_SOURCES}
)

target_compile_definitions(
    comitton
    PRIVATE
    SILENT
    RARDLL
    UNRAR
)

# ------------------------------------------------------------------------------
# 3. インクルードディレクトリの設定
# ------------------------------------------------------------------------------
file(GLOB UNRAR_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/[Uu]nrar*")

set(EXTRA_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${UNRAR_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/libavif/include
    ${CMAKE_CURRENT_SOURCE_DIR}/avif/include
)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libjxl/lib/include")
    list(APPEND EXTRA_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/libjxl/lib/include")
endif()

target_include_directories(
    comitton
    PRIVATE
    ${EXTRA_INCLUDES}
)

# ------------------------------------------------------------------------------
# 4. リンクライブラリの設定
# ------------------------------------------------------------------------------
find_library(log-lib log)
find_library(android-lib android)
find_library(jnigraphics-lib jnigraphics)

set(LINK_LIBS
    ${log-lib}
    ${android-lib}
    ${jnigraphics-lib}
)

if(TARGET jxl)
    list(APPEND LINK_LIBS jxl)
endif()
if(TARGET jxl_threads)
    list(APPEND LINK_LIBS jxl_threads)
endif()
if(TARGET avif)
    list(APPEND LINK_LIBS avif)
endif()

target_link_libraries(
    comitton
    PRIVATE
    ${LINK_LIBS}
)