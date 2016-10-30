#cmake Version
cmake_minimum_required(VERSION 2.8)

#Project Name
project( Paint_by_numbers )

#Include libraries
find_package( OpenCV REQUIRED )

#Executables
add_executable( PaintByNumbers src/main.cpp
							   src/cvsource/pencilSketch.cpp )
target_link_libraries( PaintByNumbers ${OpenCV_LIBS} )