cmake_minimum_required(VERSION 3.2)
project(qtMarkup CXX)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

QT4_WRAP_CPP(MOCSrcs convert.h fileCommand.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

ADD_EXECUTABLE(qtMarkup test.h testall.h fileCommand.cpp fileCommand.h main.cpp convert.cpp convert.h ${MOCSrcs})

TARGET_LINK_LIBRARIES(qtMarkup Qt4::QtGui Qt4::QtWebKit)


