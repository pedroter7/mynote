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