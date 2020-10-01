#!/bin/bash

# This script is a shortcut to build and run a debug version of MyNote
echo "" && \
	echo "=================== building ===================" &&\
       	echo "" && \
	meson __build && \
	ninja -C __build && \
	echo "" && \
       	echo "=================== running ===================" && \
       	echo "" && \
	__build/src/mynote
