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

/*
    This is a classic confirm exit window that asks if the user wants to save changes or not
*/

#ifndef _MYNOTE_CONFIRM_EXIT_WINDOW_HPP_
#define _MYNOTE_CONFIRM_EXIT_WINDOW_HPP_

#include "mainwindow.hpp"

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>

#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

class ConfirmExitWindow : public Gtk::ApplicationWindow {
private:
    Gtk::Box *mBox; // Root element
    Glib::RefPtr<Gtk::Builder> mBuilder;
    Glib::RefPtr<Gtk::Button> mSaveButton;
    Glib::RefPtr<Gtk::Button> mDiscartButton;
    Glib::RefPtr<Gtk::Button> mCancelButton;

    MainWindow *parentMainWindow;

public:
    const Glib::ustring WINDOW_TITLE;
    const Glib::ustring WINDOW_KEY;

    ConfirmExitWindow(MainWindow *parentMainWindow);
    ~ConfirmExitWindow();
    
    // Signal handlers
    void onClickSaveButton();
    void onClickDiscartButton();
    void onClickCancelButton();

};

#endif // _MYNOTE_CONFIRM_EXIT_WINDOW_HPP_