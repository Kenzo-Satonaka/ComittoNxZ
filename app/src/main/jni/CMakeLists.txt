cmake_minimum_required(VERSION 3.16)
project(comitton C CXX ASM)

# --- dav1d 自動コンパイルの回避設定（ここに追加） ---
set(AVIF_CODEC_DAV1D OFF CACHE BOOL "" FORCE)
set(AVIF_LOCAL_DAV1D OFF CACHE BOOL "" FORCE)
set(AVIF_BUILD_APPS OFF CACHE BOOL "" FORCE)
set(AVIF_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# --------------------------------------------------

include(FetchContent)
include(GNUInstallDirs)

set(CMAKE_BUILD_TYPE Release)

add_definitions(
        "-D__ANDROID_UNAVAILABLE_SYMBOLS_ARE_WEAK__"
        "-Werror=unguarded-availability"
)

# ローカルソースのリスト
set(
  COMITTON_SOURCES
  comitton/ImageBlur.cpp
  comitton/ImageScaleHalf.cpp
  comitton/ImageCommon.cpp
  comitton/ImageThumbnail.cpp
  comitton/ImageScaleLinear.cpp
  comitton/ImageScaleCubic.cpp
  comitton/ImageScaleLanczos3.cpp
  comitton/ImageScaleNear.cpp
  comitton/ImageScale.cpp
  comitton/ImageBright.cpp
  comitton/ImageRotate.cpp
  comitton/ImageMarginCut.cpp
  comitton/ImageSharpen.cpp
  comitton/ImageInvert.cpp
  comitton/ImageGray.cpp
  comitton/ImageHalf.cpp
  comitton/ImageColorMatrix.cpp
  comitton/ImageExternalFilter.cpp
  comitton/callImage.cpp
  comitton/TextCommon.cpp
  comitton/callText.cpp
)

add_library(
  comitton SHARED
  ${COMITTON_SOURCES}
)

# rar 解凍ライブラリのビルド
add_subdirectory(unrar)
target_sources(comitton PRIVATE comitton/callUnrar.cpp)

# 画像フォーマットデコーダーのビルド

# AVIF
add_subdirectory(dav1d)
add_subdirectory(libavif)
target_sources(comitton PRIVATE comitton/ImageAVIF.cpp)

# JXL
add_subdirectory(libjxl)
target_sources(comitton PRIVATE comitton/ImageJXL.cpp)

# 生成処理
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(comitton android jnigraphics log)
