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

#include "aboutwindow.hpp"

#include "mainwindow.hpp"

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>

#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

AboutWindow::AboutWindow() : mBuilder(Gtk::Builder::create_from_resource("/mynote/res/about_window_layout.glade")), WINDOW_TITLE("About"), WINDOW_KEY("temp_window") {
    if (mBuilder) {
        mBuilder->get_widget("main_box", mBox);

        // Add root
        add(*mBox);

        // Window properties
        set_title(WINDOW_TITLE);
        set_default_size(380, 150);
        set_position(Gtk::WIN_POS_CENTER);
        set_resizable(false);
    }
}

AboutWindow::~AboutWindow() {
    delete mBox;
}