CC := g++
CFLAGS := -Wall -Wextra -g -O3 

_sources := $(wildcard ./*.cpp)
_obj := $(patsubst ./%.cpp, ./%.o, $(_sources))

all: $(_obj)

debug : def_debug all

def_debug :
	$(eval _defflags := -D DEBUG)

./%.o: ./%.cpp
	$(CC) $(CFLAGS) $(_defflags) -c $< -o $@

.PHONY: all debug def_debug
