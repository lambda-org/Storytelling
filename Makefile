_compiler    := g++
_cflags      := -Wall -Wextra -g -O3
_lflags      := -lsfml-graphics -lsfml-window -lsfml-system -lspdlog -lfmt
_srcdir      := src
_output      := storytelling
_dirs        := $(shell find $(_srcdir) -type d)

all: $(_output)
	@echo  Done!

debug : def_debug all

def_debug :
	$(eval _makeflags := debug)

$(_output): sources
	$(_compiler) $(_cflags) -o $(_output) $(_obj) $(_lflags)

sources : dirs
	$(eval _obj := $(shell find $(_dirs) -name '*.o'))

dirs: $(_dirs)

$(_dirs):
	@make -C $@ $(_makeflags)

clean:
	rm -f $(_output)
	find $(_dirs) -name '*.o' -exec rm -f {} +

.PHONY : list dirs all $(_dirs) sources debug def_debug
