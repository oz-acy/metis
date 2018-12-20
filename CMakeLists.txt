# CMakeLists.txt for project METIS

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(CMAKE_VERBOSE_MAKEFILE 1)

#PROJECT(metis CXX)

find_package(FLEX)
find_package(BISON)

SET(CMAKE_CXX_FLAGS "-Wall -std=c++11 -O3")
#SET(CMAKE_CXX_FLAGS "-Wall -std=c++17 -O3")

FLEX_TARGET(MyScanner lex.ll lex.cc)
BISON_TARGET(MyParser parse.yy parse.cc)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

ADD_LIBRARY(metis STATIC
  charref.cpp
  stringdata.cpp sd-utf8code.cpp
  metis_base.cpp
  metis_celm.cpp
  ctext.cpp
  cattr.cpp
  strescape.cpp
  strvisitor.cpp
  ${FLEX_MyScanner_OUTPUTS}
  ${BISON_MyParser_OUTPUTS}
)

INSTALL(TARGETS metis DESTINATION lib)
INSTALL(FILES
    data.h
    parser.h
    strvisitor.h
    strescape.h
  DESTINATION
    include/metis
)


#eof
