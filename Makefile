PROGRAM = binarytree
INCLUDEDIRS = 
LIBDIRS = 
LIBS =

CXXSOURCES = binarytree.cpp \
				redblack.cpp \
				main.cpp

CXXOBJECTS = $(CXXSOURCES:.cpp=.o)
CXXFLAGS = -g -ggdb --std=c++11 -o0
CXX = g++

LDFLAGS = $(LDLIBS) $(LIBDIRS)

all: $(PROGRAM)

$(PROGRAM): $(CXXOBJECTS)
	$(CXX) -o $@ $(CXXOBJECTS) $(LDFLAGS)

tree.o: binarytree.cpp tree.h $(CXX) $(CXXFLAGS) -c -o binarytree.o binarytree.cpp

clean:
	$(RM) -f $(CXXOBJECTS) $(PROGRAM)

run: ./$(PROGRAM)
