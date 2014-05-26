# general_ledger makefile
# =======================
# Copyright 2014 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/


# Variables section
# =================

# Executable names
OUT=general_ledger

# Compiler executable name
CC=gcc

# Compiler flags
CFLAGS=-std=c11 -pedantic -Wall -Wextra
CFLAGS+=-I/usr/include/mysql -DBIG_JOINS=1  -fno-strict-aliasing  -g
C_DEBUG_FLAGS=-ggdb -DDEBUG -DDEBUG_ALL
C_RELEASE_FLAGS=-O3 -DNDEBUG

# Linker flags
LDFLAGS=-Lconfig_file_read -lconfig_file_read
LDFLAGS+=-Lstring_helpers -lstring_helpers
LDFLAGS+=-L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -lrt -ldl

# Object code files
OBJS=main.o database.o gl_errors.o gl_logging.o

# Source and clean files and globs
SRCS=$(wildcard *.c *.h)

SRCGLOB=*.c

CLNGLOB=$(OUT) $(SAMPLEOUT)
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
main: $(OBJS) string_helpers config_file_read
	@echo "Building general_ledger..."
	@$(CC) -o $(OUT) $(OBJS) $(LDFLAGS)
	@echo "Done."

# Sub libraries section
.PHONY: string_helpers
string_helpers:
	@cd string_helpers; make;

.PHONY: config_file_read
config_file_read:
	@cd config_file_read; make;

# Object files targets section
# ============================

# Object files for executable

main.o: main.c database.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

database.o: database.c database.h gl_errors.h gl_general.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

gl_errors.o: gl_errors.c gl_errors.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

gl_logging.o: gl_logging.c gl_logging.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

