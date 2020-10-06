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

#include "savewindow.hpp"

#include "mainwindow.hpp"

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/filechooser.h>
#include <gtkmm/button.h>

#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

#include <sigc++/sigc++.h>

SaveWindow::SaveWindow(MainWindow *parentMainWindow) : mBuilder(Gtk::Builder::create_from_resource("/mynote/res/save_window_layout.glade")), parentMainWindow(parentMainWindow), WINDOW_TITLE("Save File"), WINDOW_KEY("temp_window") {
    if (mBuilder) {
        mBuilder->get_widget("main_box", mBox);
        mEntry = Glib::RefPtr<Gtk::Entry>::cast_dynamic(mBuilder->get_object("file_name_entry"));
        mFileChooser = Glib::RefPtr<Gtk::FileChooser>::cast_dynamic(mBuilder->get_object("folder_dest_chooser"));
        mMessageLabel = Glib::RefPtr<Gtk::Label>::cast_dynamic(mBuilder->get_object("message_label"));

        // Get buttons and connect signals
        mCancelButton = Glib::RefPtr<Gtk::Button>::cast_dynamic(mBuilder->get_object("cancel_button"));
        mCancelButton->signal_clicked().connect(sigc::mem_fun(this, &SaveWindow::onClickCancel));
        mSaveButton = Glib::RefPtr<Gtk::Button>::cast_dynamic(mBuilder->get_object("save_button"));
        mSaveButton->signal_clicked().connect(sigc::mem_fun(this, &SaveWindow::onClickSave));

        // Add root element
        add(*mBox);

        // Window properties
        set_title(WINDOW_TITLE);
        set_default_size(380, 100);
        set_position(Gtk::WIN_POS_CENTER);
        set_resizable(false);
    }
}

SaveWindow::~SaveWindow() {
    delete mBox;
}

// Signal handlers
void SaveWindow::onClickCancel() {
    // Do nothing, just hide yourself!!
    hide();
}

void SaveWindow::onClickSave() {
    // Get path, and filename
    Glib::ustring pathToSave = mFileChooser->get_filename();
    Glib::ustring filename = mEntry->get_text();

    if (pathToSave.empty()) {
        mMessageLabel->set_text("Please, select a folder to save.");
    } else if (filename.empty()) {
        mMessageLabel->set_text("Please, enter a filename to save.");
    } else {
        pathToSave += "/";
        if (parentMainWindow->saveRoutine(pathToSave, filename)) {
            hide();
            if (parentMainWindow->getNewClicked()){
                parentMainWindow->clearWindow();
                parentMainWindow->setNewClicked(false);
            }
        } else {
            mMessageLabel->set_text("Some error occured while trying to save.");
        }
    }
}