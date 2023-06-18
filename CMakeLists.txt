cmake_minimum_required (VERSION 3.11)
project(ftxui-window
  LANGUAGES CXX
  VERSION 1.0.0
  )

include(cmake/find-ftxui.cmake)

add_library(ftxui-window
  include/ftxui-window/ftxui-window.hpp
  src/ftxui-window/ftxui-window.cpp
  )

target_include_directories(ftxui-window
  PUBLIC include
  )

target_link_libraries(ftxui-window
  PUBLIC ftxui::screen
  PUBLIC ftxui::dom
  PUBLIC ftxui::component
  )

add_subdirectory(examples)
