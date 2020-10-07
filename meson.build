# This belongs to MyNote project, see https://github.com/pedroter7/mynote

project('mynote', 'cpp', 'c', version : '1.0', default_options : ['cpp_std=c++14'])
set_variable('prefix','/usr/local/share/mynote')

gtkmm_pkgname = 'gtkmm-3.0'
gtkmm_dep = dependency(gtkmm_pkgname, version : '>=3.24.0')

gnome = import('gnome')

incdir = include_directories('include')

subdir('res')
subdir('src')

install_data('mynote.desktop', install_dir : get_option('prefix')/'share'/'applications')
