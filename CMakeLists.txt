cmake_minimum_required(VERSION 3.8)
project(cppex2)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES ikea.cpp ikea.h Item.cpp Item.h Fabric.h Furniture.h Kitchenware.h TablesAndChairs.h MoviesAndBooks.h Candy.h)
add_executable(cppex2 ${SOURCE_FILES})