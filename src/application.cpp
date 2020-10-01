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
Application is a singleton class that abstracts a Gtk::Application instance for MyNote
*/

#include "application.hpp"
#include "mainwindow.hpp"

#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>

#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

#include <map>

// MyNote app ID
const Glib::ustring Application::APP_ID = "com.github.pedroter7.mynote";

Application *Application::uniqueInstance = nullptr;

// Private constructor
Application::Application() : mGtkApplication(Gtk::Application::create(Application::APP_ID)) {
    // Create instance for each window
    windows["main_window"] = new MainWindow();
}

Application::~Application() {
    // Delete all windows
    for (auto& k : windows) {
        delete k.second;
    }
    delete uniqueInstance;
}

Application* Application::getInstance() {
    if (Application::uniqueInstance == nullptr) {
        Application::uniqueInstance = new Application();
    }
    return uniqueInstance;
}

// Abstracts a call to Gtk::Application run() method
int Application::run() {
    windows["main_window"]->show_all();
    return mGtkApplication->run(*windows["main_window"]);
}