# string_helpers makefile
# =======================
# Copyright 2014 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/


# Variables section
# =================

# Library and executable names
LIBNAME=string_helpers
OUT=lib$(LIBNAME).a

# Compiler and archiver executable names
AR=ar
CC=gcc

# Archiver flags
ARFLAGS=rcs

# Compiler flags
CFLAGS=-std=c99 -pedantic -Wall -Wextra
C_DEBUG_FLAGS=-ggdb -DDEBUG -DDEBUG_ALL
C_RELEASE_FLAGS=-O3 -DNDEBUG

# Linker flags
LDFLAGS=

# Object code files
OBJS=string_functions.o

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

# tags - makes tags file
.PHONY: tags
tags:
	@ctags *.c *.g


# Executable targets section
# ==========================

# Main library
main: $(OBJS)
	@echo "Building library..."
	@$(AR) $(ARFLAGS) $(OUT) $(OBJS)
	@echo "Done."


# Object files targets section
# ============================

# Object files for library

string_functions.o: string_functions.c string_functions.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

