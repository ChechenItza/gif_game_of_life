all:
	c++ -std=c++11 -g -Wall ./Source/main.cpp ./Source/universe.cpp `Magick++-config --cppflags --cxxflags --ldflags --libs` -I/usr/include/ImageMagick-6 -I./Headers
