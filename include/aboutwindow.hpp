/*
    MyNote : A simple Notepad-like editor
    
    Copyright (C) 2020  Pedro Tersetti Freidinger

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Contact:

    Pedro Tersetti Freidinger: pedrotersetti3@gmail.com

    All source code of MyNote is available at https://github.com/pedroter7/mynote
*/

#ifndef _MYNOTE_ABOUT_WINDOW_HPP_
#define _MYNOTE_ABOUT_WINDOW_HPP_

#include "mainwindow.hpp"

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>

#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

class AboutWindow : public Gtk::ApplicationWindow {
private:
    Gtk::Box *mBox; // Root element
    Glib::RefPtr<Gtk::Builder> mBuilder;

public:
    const Glib::ustring WINDOW_TITLE;
    const Glib::ustring WINDOW_KEY;

    AboutWindow();
    ~AboutWindow();

};

#endif // _MYNOTE_ABOUT_WINDOW_HPP_