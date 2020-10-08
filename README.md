# MyNote

MyNote is a very, very simple Notepad-like editor. Note that I've developed this small editor to learn Gtkmm, Meson Build and how to do some stuff. Thus this project has basically no design, is incomplete, and contains some bugs. You can do wathever you want with it, just take a look at the GPLV-3.0 before.

# Install

## Requirements

In order to build and run MyNote, you need to have at least those installed:

- [Gtkmm](https://www.gtkmm.org/en/) and its dependencies;
- pkg-config(https://www.freedesktop.org/wiki/Software/pkg-config/);
- [meson](https://mesonbuild.com/index.html) and its dependencies;
- ninja;

## How to

Just clone/download this repository's Master branch and run the install.sh script. Other option is to run manually meson and ninja commands. **If you change the prefix variable, remember to change the desktop entry too.**  
The build-run.sh script is a shortcut to install a debug version to a directory called \_\_build.

# Copying

MyNote is licensed under the [GNU General Public License v3.0](https://opensource.org/licenses/GPL-3.0)  
MyNote logo icon is made by [Kiranshastry](https://www.flaticon.com/br/autores/kiranshastry) from [www.flaticon.com](http://flaticon.com)
