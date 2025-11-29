CXX = g++
CXXFLAGS = -g
src := $(wildcard *.cpp)
execs := $(patsubst %.cpp,%.exe,$(src))

.SILENT:

base: $(execs)
	echo $^

%.exe: %.cpp helpers.hpp
	$(CXX) $(CXXFLAGS) $< -o $@
	echo $@ compiled
 
%.d: %.cpp
	$(CXX) -MM -MP -MT $(patsubst %.cpp,%.exe,$<) $< > $@
	echo $@ updated

cleanDeps:
	rm -f $(dependencies)

announce:
	echo src: $(src)
	echo execs: $(execs)
	echo dependencies: $(dependencies)
