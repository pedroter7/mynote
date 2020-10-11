# This belongs to MyNote, see http://github.com/pedroter7/mynote
#
# Use this Makefile to create a directory with all files needed to pack a ms installer
# for a standalone version of MyNote for windows
#
# Notice that this makefile is supposed to be executed only on Windows
# if you are running a Unix-like OS, look at build-run.sh, install.sh and meson.build scripts
#
# The reason for using make to build a distribution for windows instead of meson
# is because when passing the flag -mwindows to meson it seems to make no difference

all:
	@echo "Run this on windows only!!!"
	@echo "Run make windows-dist to create a dist directory at dist/windows/mynote-xx"

PROJECT=mynote
VERSION=1.0

CC=g++
CPPVERSION=14
CPPFLAGS=-std=c++$(CPPVERSION) -mwindows -O2 -Wall
GTKMMFLAGS=pkg-config gtkmm-3.0 --cflags --libs
CFLAGS=$(CPPFLAGS) -Iinclude/ `$(GTKMMFLAGS)` 

SRCDIR=src
RESDIR=res
DISTDIR=$(PROJECT)-$(VERSION)
DISTDIRPATH=dist/windows/$(DISTDIR)

# main target
windows-dist: $(DISTDIRPATH)
	cd $(RESDIR) && $(MAKE) compile-resources
	cd $(SRCDIR) && $(MAKE) build-source
	$(CC) -o $(DISTDIRPATH)/bin/$(PROJECT).exe $(SRCDIR)/*.o $(RESDIR)/*.o $(CFLAGS)
	cd $(RESDIR) && $(MAKE) clean
	cd $(SRCDIR) && $(MAKE) clean

$(DISTDIRPATH):
	mkdir -p $(DISTDIRPATH) $(DISTDIRPATH)/bin \
		$(DISTDIRPATH)/etc $(DISTDIRPATH)/lib $(DISTDIRPATH)/share

.PHONY: all $(DISTDIRPATH)
