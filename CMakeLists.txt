cmake_minimum_required(VERSION 3.8)
project(cppex2)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES ikea.cpp ikea.h Item.cpp Item.h Cloth.cpp Cloth.h Furniture.cpp Furniture.h KitchenUtensils.cpp KitchenUtensils.h TablesAndChairs.cpp TablesAndChairs.h MoviesAndBooks.cpp MoviesAndBooks.h)
add_executable(cppex2 ${SOURCE_FILES})