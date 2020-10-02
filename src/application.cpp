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
#include "confirmexitwindow.hpp"

#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>

#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

#include <map>
#include <mutex>

// MyNote app ID
const Glib::ustring Application::APP_ID = "com.github.pedroter7.mynote";

Application *Application::uniqueInstance = nullptr;

// Private constructor
Application::Application() : mGtkApplication(Gtk::Application::create(Application::APP_ID)), mMutex(), lastChangesSaved(true) {
    // Create instance for each window
    windows["main_window"] = new MainWindow();
    windows["temp_window"] = nullptr; // For temporary dialog windows
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

// Set a temporary window
bool Application::setTemporaryWindow(Gtk::ApplicationWindow* window, bool force) {
    std::lock_guard<std::mutex> lock(mMutex);
    if (window) {
        if (windows["temp_window"]) {
            if (force) {
                // Delete current temp_window
                delete windows["temp_window"];
            } else {
                // Can't assign new temp_window
                return false;
            }
        }

        windows["temp_window"] = window;
        return true;
    } else {
        return false;
    }
}

// Abstracts a call to Gtk::Application run() method
int Application::run() {
    windows["main_window"]->show_all();
    return mGtkApplication->run(*windows["main_window"]);
}

// Application state manipulators, setters, and getters
void Application::setSaved() {
    std::lock_guard<std::mutex> lock(mMutex);
    if (lastChangesSaved == false) {
        // Remove the * from MainWindow title
        Glib::ustring windowTitle = windows["main_window"]->get_title();
        windowTitle.replace(windowTitle.find("*"), 1, "");
        windows["main_window"]->set_title(windowTitle);
        lastChangesSaved = true;
    }
}

void Application::setUnsaved() {
    std::lock_guard<std::mutex> lock(mMutex);
    if (lastChangesSaved == true) {
        // Append an * to MainWindow title
        Glib::ustring windowTitle = windows["main_window"]->get_title();
        windowTitle = windowTitle + "*";
        windows["main_window"]->set_title(windowTitle);

        lastChangesSaved = false;
    }
}

bool Application::getChangesSaved() {
    return lastChangesSaved;
}

// Window display/hide
void Application::displayWindow(Glib::ustring windowKey) {
    windows[windowKey]->show_all();
}

void Application::hideWindow(Glib::ustring windowKey) {
    windows[windowKey]->hide();
}

// Add window to mGtkApplication
void Application::addWindow(Glib::ustring windowKey) {
    mGtkApplication->add_window(*windows[windowKey]);
}