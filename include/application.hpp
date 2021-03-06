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
    Application is a singleton class that abstracts a Gtk::Application instance for MyNote, 
    stores the instances for all windows used in the application,
    and has info about the applications general state
*/

#ifndef _MYNOTE_APPLICATION_HPP_
#define _MYNOTE_APPLICATION_HPP_

#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>

#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

#include <map>
#include <mutex>

class Application {
private:
    Application();

    static Application *uniqueInstance;

    Glib::RefPtr<Gtk::Application> mGtkApplication;

    // Instances of each window
    std::map<Glib::ustring, Gtk::ApplicationWindow*> windows;

    mutable std::mutex mMutex; // Used to control access to state variables

    // Application state variables
    bool lastChangesSaved;

public:
    ~Application();
    static Application* getInstance();

    // MyNote app ID, defined in application.cpp: com.github.pedroter7.mynote
    static const Glib::ustring APP_ID;

    // Set a temporary window
    bool setTemporaryWindow(Gtk::ApplicationWindow* window, bool force=false);

    // Abstracts a call to Gtk::Application run() method
    int run();

    // Application state manipulators, setters, and getters
    void setSaved();
    void setUnsaved();
    bool getChangesSaved();

    // Window display/hide/add
    void displayWindow(Glib::ustring windowKey);
    void hideWindow(Glib::ustring windowKey);
    // Add window to mGtkApplication
    void addWindow(Glib::ustring windowKey);

};


#endif // _MYNOTE_APPLICATION_HPP_