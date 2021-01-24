cmake_minimum_required(VERSION 3.19)

project(ChineseChecker VERSION 1.0)

set(HEADERS
  Board.hpp
  Checker.hpp
  Coordinate.hpp
  Function.hpp
  List.hpp
  Player.hpp
  SearchTree.hpp
  TreeNode.hpp
  )

set(SOURCES
  Board.cpp
  Checker.cpp
  Coordinate.cpp
  Function.cpp
  Player.cpp
  SearchTree.cpp
  TreeNode.cpp
  )

add_executable(ChineseChecker Main.cpp ${HEADERS} ${SOURCES})



