#!/bin/bash

# This script is part of MyNote, see http://github.com/pedroter7/mynote

# Create a distribution file  
# This script is necessary to prevent including unecessary files inside the release archive
# since meson doesn't provide (yet) an easy way to do that using meson dist

PROJECT=mynote
VERSION=1.0
DISTNAME=$PROJECT-$VERSION
ROOTDIR=$(pwd)
DISTDIR=$ROOTDIR/dist/linux

# Create the dist directory and copy files that will be packed
mkdir -p $DISTDIR/$DISTNAME &&\
	cp -Rv include res src $DISTDIR/$DISTNAME &&\
	cp -v LICENSE mynote.desktop install.sh meson.build README.md $DISTDIR/$DISTNAME &&\
	
# Pack the distribution
cd $DISTDIR && tar czvf $DISTNAME.tar.gz $DISTNAME &&\

# Remove temporary directories
cd $ROOTDIR && rm -rf $DISTDIR/$DISTNAME
