CXX = g++
CXXFLAGS = -g 
src := $(wildcard *.cpp)
execs := $(patsubst %.cpp,%.exe,$(src))

dependencies := $(patsubst %.cpp,%.d,$(src))
-include $(dependencies)

.PHONY: base cleanDeps

.SILENT:

base: $(execs) 
	echo compiling any modified cpp files

%.exe: %.cpp
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