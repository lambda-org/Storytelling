_checkheader := tl/expected.hpp
_checkso     := sfml-graphics sfml-system sfml-window pugixml spdlog

_compiler    := g++
_cflags      := -Wall -Wextra -Wno-switch -g -O3 -std=c++17
_lflags      := -lsfml-graphics -lsfml-window -lsfml-system -lspdlog -lfmt -lpugixml
_srcdir      := src
_outdir      := program
_output      := storytelling
_dirs        := $(shell find $(_srcdir) -type d)
_includedirs := /usr/include \
                /usr/local/include \
                /opt/homebrew/include \
                /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include \
                /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include

debug : def_debug all

def_debug:
	@echo Making project in DEBUG mode
	$(eval _makeflags := debug)
	$(eval _outsubdir := debug)

release : def_release all

def_release :
	$(eval _outsubdir := release)

all: deps $(_output)
	@echo Done!

$(_output): sources
	$(_compiler) $(_cflags) -o $(_outdir)/$(_outsubdir)/$(_output) $(_obj) $(_lflags)

sources: dirs
	$(eval _obj := $(shell find $(_srcdir) -name '*.o'))

dirs: $(_dirs)
	@mkdir -p $(_outdir)
	@mkdir -p $(_outdir)/$(_outsubdir)

$(_dirs):
	@make -C $@ $(_makeflags)

clean: rm_executable rm_obj

rm_obj :
	find $(_dirs) -name '*.o' -exec rm -f {} +

rm_executable :
	find $(_outdir) -name $(_output) -exec rm -f {} +

deps: _info _check_so _check_headers
	@echo Dependencies checked, bulding project

_info :
	@echo Checking dependencies...

_check_so: $(foreach lib,$(_checkso),check_lib_$(lib))

$(foreach lib,$(_checkso),check_lib_$(lib)):
	@echo -n "Checking for $(@:check_lib_%=%)... "
	@if ldconfig -p | grep -q "$(@:check_lib_%=%)"; then \
					echo "found"; \
	else \
					echo "not found"; \
					exit 1; \
	fi

_check_headers:
	@for header in $(_checkheader); do \
		echo -n "Checking for header $$header... "; \
		found=false; \
		for dir in $(_includedirs); do \
			if [ -f "$$dir/$$header" ]; then \
				echo "found"; \
				found=true; \
				break; \
			fi; \
		done; \
		if ! $$found; then \
			echo "not found"; \
			exit 1; \
		fi; \
	done

.PHONY: list dirs all $(_dirs) sources debug def_debug deps _check_so _check_headers _info rm_obj rm_executable release def_release

