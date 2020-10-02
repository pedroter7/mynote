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

#include "confirmexitwindow.hpp"

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>

#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

#include <sigc++/sigc++.h>

#include <iostream>

ConfirmExitWindow::ConfirmExitWindow() : mBuilder(Gtk::Builder::create_from_resource("/mynote/res/confirm_exit_dialog_layout.glade")), WINDOW_TITLE("Confirm Exit"), WINDOW_KEY("temp_window") {
    if (mBuilder) {
        mBuilder->get_widget("main_box", mBox);
        mSaveButton = Glib::RefPtr<Gtk::Button>::cast_dynamic(mBuilder->get_object("save_button"));
        mDiscartButton = Glib::RefPtr<Gtk::Button>::cast_dynamic(mBuilder->get_object("discart_button"));
        mCancelButton = Glib::RefPtr<Gtk::Button>::cast_dynamic(mBuilder->get_object("cancel_button"));

        // Connect signals to buttons
        mSaveButton->signal_clicked().connect(sigc::mem_fun(this, &ConfirmExitWindow::onClickSaveButton));
        mDiscartButton->signal_clicked().connect(sigc::mem_fun(this, &ConfirmExitWindow::onClickDiscartButton));
        mCancelButton->signal_clicked().connect(sigc::mem_fun(this, &ConfirmExitWindow::onClickCancelButton));

        // Add root
        add(*mBox);

        // Window properties
        set_title(WINDOW_TITLE);
        set_default_size(300, 250);
        set_position(Gtk::WIN_POS_CENTER);
        set_resizable(false);
    }
}

ConfirmExitWindow::~ConfirmExitWindow() {
    delete mBox;
}

// Signal handlers
void ConfirmExitWindow::onClickSaveButton() {
    std::cout << "Save clicked" << std::endl;

}

void ConfirmExitWindow::onClickDiscartButton() {
    std::cout << "Discart clicked" << std::endl;
}

void ConfirmExitWindow::onClickCancelButton() {
    std::cout << "Cancel clicked" << std::endl;
}