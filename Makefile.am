AUTOMAKE_OPTIONS = foreign

AM_CPPFLAGS = -I$(srcdir)/src
AM_CFLAGS = -I$(srcdir)/src

bin_PROGRAMS = out/storytelling
storytelling_SOURCES = src/main.cpp
storytelling_LDADD = -lcsfml-graphics -lcsfml-window -lcsfml-system
storytelling_OBJECTS = build/main.o

$(srcdir)/out:
	mkdir -p $(srcdir)/out

$(srcdir)/build:
	mkdir -p $(srcdir)/build

out/storytelling: $(storytelling_OBJECTS) $(srcdir)/out
	$(LINK) $(storytelling_OBJECTS) $(storytelling_LDADD) -o $@

build/%.o: src/%.c | $(srcdir)/build
	$(COMPILE) -o $@ -c $<

clean-local:
	rm -rf $(srcdir)/build/*