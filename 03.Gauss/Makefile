CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -Werror
CPPFLAGS += -I../external/eigen -I../external/eigen3 -I/usr/include/eigen3
GTEST_LIBS ?= -lgtest -lgtest_main -pthread

COMMON_SRC = util.cpp Gauss_solve.cpp

.PHONY: all release debug utest run_utest run_itest depends clean cleanall mrproper

all: depends run_utest run_itest

release: gauss

gauss: Gauss_main.cpp $(COMMON_SRC) util.h Gauss_solve.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -O3 -DNDEBUG Gauss_main.cpp $(COMMON_SRC) -o $@

debug: Gauss_main.cpp $(COMMON_SRC) util.h Gauss_solve.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -g -DDEBUG Gauss_main.cpp $(COMMON_SRC) -o $@

utest: Gauss_test.cpp $(COMMON_SRC) util.h Gauss_solve.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -g -DDEBUG Gauss_test.cpp $(COMMON_SRC) -o $@ $(GTEST_LIBS)

run_utest: utest
	./utest

run_itest: release
	./integration_test.sh

depends:
	@touch Makefile.hdrdep

clean:
	- rm -f *.o *.d.o *.r.o *.hdrdep.bak gauss debug utest

cleanall: clean
	- rm -f Makefile.hdrdep

mrproper: cleanall
