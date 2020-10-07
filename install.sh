# Execute this to install MyNote
#!/bin/bash

meson --buildtype=release __build &&\
	sudo ninja -C __build install
