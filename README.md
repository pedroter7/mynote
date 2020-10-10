# MyNote

MyNote is a very, very simple Notepad-like editor. Note that I've developed this small editor to learn Gtkmm, Meson Build and how to do some stuff. Thus this project has basically no design, is kinda incomplete, and contains some bugs. You can do wathever you want with it, just take a look at the GPLV-3.0 before.

# Releases:

- **Latest stable: 1.0**

# Install

## Requirements

In order to build and run MyNote, you need to have at least those installed:

#### Linux:

- [Gtkmm](https://www.gtkmm.org/en/) and its dependencies;
- pkg-config(https://www.freedesktop.org/wiki/Software/pkg-config/);
- [meson](https://mesonbuild.com/index.html) and its dependencies;
- ninja;

### Windows:

- [MSYS2](https://www.msys2.org/);

Installing those packages inside MSYS2 should be enough:
````bash
pacman -S --needed mingw-w64-{i686,x86_64}-{toolchain,meson,pkg-config,glib2}
pacman -S mingw-w64-x86_64-{gtkmm3, glib2,atk,pango,cairo,gdk-pixbuf2,librsvg,graphene,libepoxy,libsigc++3,glibmm,pangomm,atkmm}
pacman -S mingw-w64-x86_64-{shared-mime-info,adwaita-icon-theme}
```


## How to install - Linux

- Download the [distribution file](https://github.com/pedroter7/mynote/blob/master/dist/linux/mynote-1.0.tar.gz?raw=true);
- Go to the folder where the .tar.gz file is and do the following to install MyNote to /usr/local/bin:
```bash
tar xvf mynote-*.tar.gz
cd mynote-* # * is the version number just downloaded
./install.sh # This script executes the following: meson __build; ninja -C __build; ninja -C __build install
```
- In order to build mynote only locally or override some predefined meson variables such as prefix, you can manually call meson and ninja instead of executing the install script

## How to uninstall - Linux

- In case you have removed the download files; download the [distribution file](https://github.com/pedroter7/mynote/blob/master/dist/linux/mynote-1.0.tar.gz?raw=true) again;
- Go to the folder where the .tar.gz file is and do the following to uninstall MyNote (Notice that if you have overrided any default directory, you must override it again to correctly uninstall MyNote):
```bash
tar xvf mynote-*.tar.gz
cd mynote-* # * is the version number just downloaded
meson __build
ninja -C __build # Still not sure if this step is needed to uninstall
ninja -C __build uninstall
```

## How to install - Windows

*Still working on this...*

# Debug build - Linux / Windows

*When using Windows, do this using MSYS2*  

- You can manually call meson and ninja, just remember to pass to meson the flag --buildtype=debug since the default is release;
- Another option is to use the handy build-run.sh script, the script make the following calls:
```bash
meson --buildtype=debug __build
ninja -C __build
__build/src/mynote # Run the build
```
 
# Copying

MyNote is licensed under the [GNU General Public License v3.0](https://opensource.org/licenses/GPL-3.0)  
MyNote logo icon is made by [Kiranshastry](https://www.flaticon.com/br/autores/kiranshastry) from [www.flaticon.com](http://flaticon.com)
