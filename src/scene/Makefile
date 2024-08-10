CC := g++
CFLAGS := -Wall -Wextra -Wno-switch -g -O3 -std=c++17

_sources := $(wildcard ./*.cpp)
_obj := $(patsubst ./%.cpp, ./%.o, $(_sources))

all: $(_obj)

debug : def_debug all

def_debug :
	$(eval _defflags := -D DEBUG)

./%.o: ./%.cpp
	$(CC) $(CFLAGS) $(_defflags) -c $< -o $@

.PHONY: all debug def_debug
