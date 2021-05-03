cmake_minimum_required(VERSION 3.10)
set(CMAKE_VERBOSE_MAKEFILE 1)
project(metis CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(eunomia REQUIRED)

find_package(BISON REQUIRED)
BISON_TARGET(MetisParser parse.yy
  ${CMAKE_CURRENT_BINARY_DIR}/parse.cpp
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.h
)

find_package(FLEX REQUIRED)
FLEX_TARGET(MetisScanner lex.ll
  ${CMAKE_CURRENT_BINARY_DIR}/lex.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MetisScanner MetisParser)


# ソースファイルとヘッダファイル
set(METIS_SOURCES
  charref.cpp
  stringdata.cpp
  element.cpp
  elm_ce.cpp
  elm_text.cpp
  elm_attr.cpp
  stringescape.cpp
  ${FLEX_MetisScanner_OUTPUTS}
  ${BISON_MetisParser_OUTPUTS}
)
set(METIS_HEADERS
  data.h
  stringvisitor.h
  stringescape.h
  ${CMAKE_CURRENT_BINARY_DIR}/parser.h
)


# リリースビルドライブラリ
ADD_LIBRARY(metis STATIC ${METIS_SOURCES})
target_compile_options(metis PRIVATE
  $<$<CXX_COMPILER_ID:GNU>:-Wall -O3>
)
target_compile_definitions(metis PRIVATE NDEBUG)
target_include_directories(metis PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  $<$<BOOL:MINGW>:/usr/include>
)
target_link_libraries(metis PRIVATE eunomia)


# テストプログラム
add_executable(metis-test
  main.cpp
)
target_compile_definitions(metis-test PRIVATE NDEBUG)
target_include_directories(metis-test PRIVATE
  ${EUNOMIA_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  $<$<BOOL:MINGW>:/usr/include>
)
target_link_options(metis-test PRIVATE
  $<$<CXX_COMPILER_ID:GNU>:-static>
)
target_link_libraries(metis-test metis eunomia ${FLEX_LIBRARIES})


# インストール設定
install(TARGETS metis
  EXPORT metis-export
  ARCHIVE DESTINATION lib
  INCLUDES DESTINATION include
  PUBLIC_HEADER DESTINATION include/metis
)

install(EXPORT metis-export
  FILE metis-config.cmake
  DESTINATION share/cmake/metis/
#  EXPORT_LINK_INTERFACE_LIBRARIES
)


#eof
