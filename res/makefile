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
	@echo "Run make windows-dist on root dir to create a dist directory at dist/windows/mynote-xx"

PROJECT=mynote
VERSION=1.0

CC=g++
GTKMMFLAGS=pkg-config gtkmm-3.0 --cflags --libs

CRES=glib-compile-resources
RESCFILE=resources.c
RESFLAGS=--generate-source --target=$(RESCFILE)
GRESOURCES=resources.gresources.xml

DISTDIR=$(PROJECT)-$(VERSION)
DISTDIRPATH=dist/windows/$(DISTDIR)

# Compile the resources
compile-resources: img/* *.glade $(GRESOURCES)
	$(CRES) $(RESFLAGS) $(GRESOURCES)
	$(CC) -c $(RESCFILE) `$(GTKMMFLAGS)`

clean:
	rm *.o $(RESCFILE)

.PHONY: all clean
