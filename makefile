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

PROJECTDIR=$(shell pwd)
SRCDIR=src
RESDIR=res
DISTDIR=$(PROJECT)-$(VERSION)
DISTDIRPATH=$(PROJECTDIR)/dist/windows/$(DISTDIR)
DISTBINDIR=$(DISTDIRPATH)/bin
DISTETCDIR=$(DISTDIRPATH)/etc
DISTLIBDIR=$(DISTDIRPATH)/lib
DISTSHAREDIR=$(DISTDIRPATH)/share

# main target
windows-dist: $(DISTDIRPATH) copy-files
	cd $(RESDIR) && $(MAKE) compile-resources
	cd $(SRCDIR) && $(MAKE) build-source
	$(CC) -o $(DISTBINDIR)/$(PROJECT).exe $(SRCDIR)/*.o $(RESDIR)/*.o $(CFLAGS)
	cd $(RESDIR) && $(MAKE) clean
	cd $(SRCDIR) && $(MAKE) clean

$(DISTDIRPATH):
	mkdir -p $(DISTDIRPATH) $(DISTBINDIR) \
		$(DISTETCDIR) $(DISTLIBDIR) $(DISTSHAREDIR)

# Copy dlls and exes

MINGWDIR=/mingw64
MINGWBINDIR=$(MINGWDIR)/bin
MINGWETCDIR=$(MINGWDIR)/etc
MINGWLIBDIR=$(MINGWDIR)/lib
MINGWSHAREDIR=$(MINGWDIR)/share

# Needed files to bin directory
BINDIRFILES=*atk*.dll *brotli*.dll *bz*.dll *cairo*.dll *datrie*.dll *epoxy*.dll\
	    *expat*.dll *ffi*.dll *fontconfig*.dll *freetype*.dll *fribidi*.dll\
	    *gcc_s_seh*.dll *gdk*.dll *gio*dll *glib*.dll *gmodule*.dll *gobject*.dll\
	    *graphite*.dll *gthread*.dll *gtk*.dll *harfbuzz*.dll *iconv*.dll *intl*.dll\
	    *lzma*.dll *pango*.dll *pcre*.dll *pixman*.dll *libpng* *sigc*.dll *std*.dll\
	    *thai*.dll *winpthread*.dll *xml*.dll *mime-database* *zlib*.dll\
	    gdbus* gdk-pixbuf*.exe

# Needed files to etc directory
ETCDIRFILES=gtk-3.0

# Needed files to lib directory
LIBDIRFILES=gdkmm-3.0 gdk-pixbuf-2.0 giomm-2.4 girepository-1.0 glib-2.0 glibmm-2.4 gtk*-3.0

# Needed files to share directory
SHAREDIRFILES=glib-2.0 icons locale

copy-files: $(DISTDIRPATH)
	cd $(MINGWBINDIR) && cp -Rv $(BINDIRFILES) $(DISTBINDIR)
	cd $(MINGWETCDIR) && cp -Rv $(ETCDIRFILES) $(DISTETCDIR)
	cd $(MINGWLIBDIR) && cp -Rv $(LIBDIRFILES) $(DISTLIBDIR)
	cd $(MINGWSHAREDIR) && cp -Rv $(SHAREDIRFILES) $(DISTSHAREDIR)

.PHONY: all $(DISTDIRPATH) copy-files
