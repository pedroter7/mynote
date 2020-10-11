# This belongs to MyNote, see http://github.com/pedroter7/mynote
#
# Use this Makefile to create a directory with all files needed to pack a ms installer
# for a standalone version of MyNote for windows
#
# Notice that this makefile is supposed to be executed only on Windows
# if you are running a Unix-like OS, look at build-run.sh, install.sh and meson.build scripts
#

all:
	@echo "Run this on windows only!!!"
	@echo "Run make windows-dist to create a dist directory at dist/windows/mynote-xx"

PROJECT=mynote
VERSION=1.0

INC=../include

CC=g++
CPPVERSION=14
CPPFLAGS=-std=c++$(CPPVERSION) -mwindows -O2 -Wall
GTKMMFLAGS=pkg-config gtkmm-3.0 --cflags --libs
CFLAGS=$(CPPFLAGS) -I$(INC)/ `$(GTKMMFLAGS)` 


MAINDEP=$(INC)/*.hpp *.cpp

build-source: $(MAINDEP)
	$(CC) -c *.cpp $(CFLAGS)

clean:
	rm *.o

.PHONY: all clean
