cmake_minimum_required(VERSION 3.16)
project(comitton C CXX ASM)

# FetchContent などのモジュールを読み込み
include(FetchContent)
include(GNUInstallDirs)

set(CMAKE_BUILD_TYPE Release)

add_definitions(
        "-D__ANDROID_UNAVAILABLE_SYMBOLS_ARE_WEAK__"
        "-Werror=unguarded-availability"
)

# comitton ソース
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
  comitton/callUnrar.cpp
)

# unrar ソース（jni/unrar を参照するため 相対パスは unrar/ ）
set(
  UNRAR_SOURCES
  unrar/cmddata.cpp
  unrar/consio.cpp
  unrar/extract.cpp
  unrar/filestr.cpp
  unrar/recvol.cpp
  unrar/rs.cpp
  unrar/scantree.cpp
  unrar/ui.cpp
)

# unrar をスタティックライブラリとして作成
add_library(unrar STATIC ${UNRAR_SOURCES})
target_compile_definitions(unrar PRIVATE SILENT RARDLL)
target_include_directories(unrar PUBLIC unrar)

# comitton 共有ライブラリ作成
add_library(comitton SHARED ${COMITTON_SOURCES})
target_link_libraries(comitton unrar android jnigraphics log)

# JXL
add_subdirectory(libjxl)
target_sources(comitton PRIVATE comitton/ImageJXL.cpp)

# 生成処理
include_directories(${CMAKE_CURRENT_SOURCE_DIR})