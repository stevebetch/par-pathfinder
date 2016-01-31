#------------------------------------------------------------------------------
# $Id: Makefile,v 1.17 2003/08/07 19:05:53 emarkus Exp $
# $Source: /usr/cvsroot/project_pathfind/Makefile,v $
#------------------------------------------------------------------------------

ICC=0
VERSION = 0.1.0

ifeq ($(ICC), 0)
CXX = g++
CXXFLAGS = -Wall -g -O3 -DNDEBUG -std=c++11
CXXFLAGS_G = -Wall -g -std=c++11
AR = ar
ARFLAGS = cr
else
CXX = icc
CXXFLAGS = -O3 -ipo -xK -DNDEBUG -tpp6
CXXFLAGS_G = -g
AR = xiar
ARFLAGS = cr
endif

PATHFIND = pathfind

PATHFIND_G = pathfind_g

LIBPATHFIND = lib$(PATHFIND).a

LIBPATHFIND_G = lib$(PATHFIND_G).a

LIBPATHFIND_SRC = \
  astar.cpp \
  environment.cpp \
  error.cpp \
  fringesearch.cpp \
  idastar.cpp \
  search.cpp \
  searchutils.cpp \
  statistics.cpp \
  tiling.cpp \
  util.cpp \
  version.cpp

LIBPATHFIND_OBJ = $(LIBPATHFIND_SRC:.cpp=.o)

LIBPATHFIND_OBJ_G = $(LIBPATHFIND_SRC:.cpp=_g.o)

EXAMPLE = serial

EXAMPLE_G = serial_g

EXAMPLE_SRC = driver.cpp map.cpp mainLoop.cpp wrapSearch.cpp 

EXAMPLE_OBJ = $(EXAMPLE_SRC:.cpp=.o)

EXAMPLE_OBJ_G = $(EXAMPLE_SRC:.cpp=_g.o)

all: $(LIBPATHFIND) $(EXAMPLE) $(LIBPATHFIND_G) $(EXAMPLE_G)

$(LIBPATHFIND): $(LIBPATHFIND_OBJ)
	$(AR) $(ARFLAGS) $@ $(LIBPATHFIND_OBJ)

$(LIBPATHFIND_G): $(LIBPATHFIND_OBJ_G)
	$(AR) $(ARFLAGS) $@ $(LIBPATHFIND_OBJ_G)

$(EXAMPLE): $(EXAMPLE_OBJ) $(LIBPATHFIND)
	$(CXX) $(CXXFLAGS) -o $@ $(EXAMPLE_OBJ) -L. -l$(PATHFIND)

$(EXAMPLE_G): $(EXAMPLE_OBJ_G) $(LIBPATHFIND_G)
	$(CXX) $(CXXFLAGS_G) -o $@ $(EXAMPLE_OBJ_G) -L. -l$(PATHFIND_G)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

%_g.o: %.cpp
	$(CXX) -c $(CXXFLAGS_G) -o $@ $<

version.cpp: version.cpp.in
	sed "s/PATHFIND_VERSION/\"$(VERSION)\"/" <$< >$@

# Rules for dependency file generation
%.d: %.cpp
	set -e; $(CXX) -MM $(CXXFLAGS) $< | sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; [ -s $@ ] || rm -f $@

%_g.d: %.cpp
	set -e; $(CXX) -MM $(CXXFLAGS_G) $< | sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; [ -s $@ ] || rm -f $@

clean:
	-rm *.o *.d $(LIBPATHFIND) $(EXAMPLE)

tags:
	etags `find . -name "*.cpp" -o -name "*.h"`	

.PHONY: clean tags

.SUFFIXES: .cpp

# Include dependency files
include $(LIBPATHFIND_SRC:.cpp=.d)
include $(EXAMPLE_SRC:.cpp=.d)
include $(LIBPATHFIND_SRC:.cpp=_g.d)
include $(EXAMPLE_SRC:.cpp=_g.d)
