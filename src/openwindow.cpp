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

#include "openwindow.hpp"

#include "mainwindow.hpp"

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/filechooser.h>
#include <gtkmm/button.h>

#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

#include <sigc++/sigc++.h>

OpenWindow::OpenWindow(MainWindow *parentMainWindow) : mBuilder(Gtk::Builder::create_from_resource("/mynote/res/open_window_layout.glade")), parentMainWindow(parentMainWindow), WINDOW_TITLE("Open File"), WINDOW_KEY("temp_window") {
    if (mBuilder) {
        mBuilder->get_widget("main_box", mBox);
        mFileChooser = Glib::RefPtr<Gtk::FileChooser>::cast_dynamic(mBuilder->get_object("file_chooser"));
        mMessageLabel = Glib::RefPtr<Gtk::Label>::cast_dynamic(mBuilder->get_object("message_label"));

        // Get buttons and connect signals
        mCancelButton = Glib::RefPtr<Gtk::Button>::cast_dynamic(mBuilder->get_object("cancel_button"));
        mCancelButton->signal_clicked().connect(sigc::mem_fun(this, &OpenWindow::onClickCancel));
        mOpenButton = Glib::RefPtr<Gtk::Button>::cast_dynamic(mBuilder->get_object("open_button"));
        mOpenButton->signal_clicked().connect(sigc::mem_fun(this, &OpenWindow::onClickOpen));

        // Add root element
        add(*mBox);

        // Window properties
        set_title(WINDOW_TITLE);
        set_default_size(380, 100);
        set_position(Gtk::WIN_POS_CENTER);
        set_resizable(false);
    }
}

OpenWindow::~OpenWindow() {
    delete mBox;
}

// Signal handlers
void OpenWindow::onClickCancel() {
    // Do nothing, just hide yourself!!
    hide();
}

void OpenWindow::onClickOpen() {
    Glib::ustring file = mFileChooser->get_filename();
    if (file.empty()) {
        mMessageLabel->set_text("Please, choose a file.");
    } else {
        if (!parentMainWindow->openRoutine(file)) {
            mMessageLabel->set_text("An error occured when trying to open the selected file.");
        } else {
            hide();
        }
    }
    
}