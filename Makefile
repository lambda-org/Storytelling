PROJECT 	:= cpp
OUTPUT_FILE := storytelling
CFLAGS 		:= -Wall -Wextra -g -O3
LFLAGS   	:= -lsfml-graphics -lsfml-window -lsfml-system

# ------------------------- Do not edit ----------------------------------
_srcdir     := src
_builddir	:= build
_output     := $(OUTPUT_FILE)
_cflags 	:= $(CFLAGS)
_lflags 	:= $(LFLAGS)

ifeq ($(PROJECT), cpp)
	_type = .cpp
	_compiler = g++
else
	_type = .c
	_compiler = gcc
endif

_sources    := $(wildcard src/*$(_type))
_obj	    := $(patsubst $(_srcdir)/%$(_type), $(_builddir)/%.o, $(_sources))

all: dirs $(_output)
	@echo Done!

dirs :
	@mkdir -p $(_builddir)

$(_output): $(_obj) 
	$(_compiler) $(_cflags) -o $(_output) $(_obj) $(LFLAGS)

$(_builddir)/%.o: $(_srcdir)/%$(_type)
	$(_compiler) $(_cflags) -c $< -o $@

clean:
	rm -f $(_output)
	rm -f $(_builddir)/*.o


list :
	@echo "all clean"

.PHONY : list clean dirs all