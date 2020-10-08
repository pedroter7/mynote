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

#ifndef _MYNOTE_MAIN_WINDOW_HPP_
#define _MYNOTE_MAIN_WINDOW_HPP_

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/textview.h>
#include <gtkmm/menuitem.h>

#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

class MainWindow : public Gtk::ApplicationWindow {
private:
    Gtk::Box *mBox; // Root element of the layout
    Glib::RefPtr<Gtk::Builder> mBuilder;
    Glib::RefPtr<Gtk::TextView> mTextArea;
    // File menu items
    Glib::RefPtr<Gtk::MenuItem> mMenuItem_new;
    Glib::RefPtr<Gtk::MenuItem> mMenuItem_open;
    Glib::RefPtr<Gtk::MenuItem> mMenuItem_save;
    Glib::RefPtr<Gtk::MenuItem> mMenuItem_saveAs;
    Glib::RefPtr<Gtk::MenuItem> mMenuItem_quit;
    // Help menu items
    Glib::RefPtr<Gtk::MenuItem> mMenuItem_about;
    Glib::ustring openFilePath;
    Glib::ustring openFileName;

public:
    const Glib::ustring WINDOW_TITLE;
    const Glib::ustring WINDOW_KEY; // For reference in an instace of Application class

    MainWindow();
    ~MainWindow();

    // Create and run a Gtk::MessageDialog and return its return value
    int messageDialog(Glib::ustring title, Glib::ustring message);
    // Create a window that asks for user if she wants to save changes
    // Return: 0 for save, 1 for discart, 2 for cancel
    int confirmExitDialog(bool cancelButton=false);

    // Returns the window to initial state
    void clearWindow();

    // Event handlers
    // File menu items
    void onActivateMenuItem_new();
    void onActivateMenuItem_open();
    void onActivateMenuItem_save();
    void onActivateMenuItem_saveAs();
    void onActivateMenuItem_quit();
    // Help menu items
    void onActivateMenuItem_about();
    // Changes in the text area
    void onTextChanged();
    
    bool onDestroy(GdkEventAny* event);

    // Routines
    int confirmExitRoutine(bool cancelButton=true);
    bool saveRoutine(Glib::ustring path, Glib::ustring filename);
    bool openRoutine(Glib::ustring pathToFile);

};

#endif // _MYNOTE_MAIN_WINDOW_HPP_