CXX = g++
CXXFLAGS = -g
src := $(wildcard *.cpp)
execs := $(patsubst %.cpp,%.exe,$(src))

.SILENT:

base: $(execs)
	echo $^

%.exe: %.cpp helpers.hpp
	$(CXX) $(CXXFLAGS) $< -o $@
	echo $@ 
