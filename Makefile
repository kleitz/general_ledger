# general_ledger makefile
# =======================
# Copyright 2014 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/


# Variables section
# =================

# Files
db_program	 	:= gl_db
reports_program	:= gl_reports
sources      	:= $(wildcard *.c)
libraries    	:=
objects       	 = $(subst .c,.o,$(sources))
depends       	 = $(subst .c,.d,$(sources))
db_objects   	:=
reports_objects :=

# Compile options
database     := mysql

# Compiler flags
CFLAGS  = -std=c99 -pedantic -Wall -Wextra
CFLAGS += -Ilib
C_DEBUG_FLAGS   := -ggdb -DDEBUG -DDEBUG_ALL
C_RELEASE_FLAGS := -O3 -DNDEBUG

# Linker flags
LDFLAGS :=

# Clean files and globs
CLNGLOB=$(program) $(objects) $(libraries) $(depends)
CLNGLOB+=$(db_program) $(reports_program)
CLNGLOB+=*~ *.o *.gcov *.out *.gcda *.gcno


# Build targets section
# =====================

default: debug

# debug - builds objects with debugging info
.PHONY: debug
debug: CFLAGS+=$(C_DEBUG_FLAGS)
debug: main

# release - builds with optimizations and without debugging info
.PHONY: release
release: CFLAGS+=$(C_RELEASE_FLAGS)
release: main

# clean - removes ancilliary files from working directory
.PHONY: clean
clean:
	-@rm $(CLNGLOB) 2>/dev/null

# docs - makes Doxygen documentation:
.PHONY: docs
docs:
	@doxygen
	-@cd latex; make; cd ..
	@if [ ! -d docs ]; then \
		mkdir docs; fi
	@echo "Copying reference manual to docs..."
	@cp latex/refman.pdf docs 
	@echo "Done."

# lint - runs splint with normal checking
.PHONY: lint
lint:
	@splint $(SRCGLOB)

# linteasy - runs splint with weak checking
.PHONY: linteasy
linteasy:
	@splint -weak $(SRCGLOB)

# tags - makes tags file
.PHONY: tags
tags:
	@ctags *.c *.g


# Executable targets section
# ==========================

# Main executable
.PHONY: main
main: $(db_program) $(reports_program)

include lib/database/module.mk
include lib/database/$(database)/module.mk
include lib/gl_general/module.mk
include lib/file_ops/module.mk
include lib/datastruct/module.mk

include progs/gl_db/module.mk
include progs/gl_reports/module.mk

$(db_program):	$(db_objects) $(libraries)
	@echo "Building gl_db..."
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "Done."

$(reports_program):	$(reports_objects) $(libraries)
	@echo "Building gl_reports..."
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "Done."


# Dependencies
# ============

-include $(depends)

%.d: %.c
	@echo "Building dependencies for $<..."
	@$(CC) -M $(CFLAGS) $< > $@.tmp; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@; \
		rm -f $@.tmp

