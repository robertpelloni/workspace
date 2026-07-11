CXX = g++
CXXFLAGS = -std=c++11 -I. -O3 -Wall -shared -fPIC
LDFLAGS = -lfluidsynth
PYBIND_INCLUDES = $(shell python3 -m pybind11 --includes)
EXTENSION = $(shell python3-config --extension-suffix)

all: tests/run_tests extension

extension: hymn_player_ext$(EXTENSION)

hymn_player_ext$(EXTENSION): src/engine/HymnPlayerBinding.cpp src/engine/HymnPlayer.cpp
	$(CXX) $(CXXFLAGS) $(PYBIND_INCLUDES) $^ -o $@ $(LDFLAGS)

tests/run_tests: tests/HymnPlayerTests.cpp src/engine/HymnPlayer.cpp
	$(CXX) -std=c++11 -I. -o $@ $^ $(LDFLAGS)

clean:
	rm -f tests/run_tests
	rm -f hymn_player_ext*.so
