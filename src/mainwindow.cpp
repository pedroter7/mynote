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

#include "mainwindow.hpp"
#include "application.hpp"

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/textview.h>
#include <gtkmm/menuitem.h>

#include <glibmm/refptr.h>

#include <sigc++/sigc++.h>

#include <iostream>

MainWindow::MainWindow() : mBuilder(Gtk::Builder::create_from_resource("/mynote/res/mainwindow_layout.glade")), WINDOW_TITLE("MyNote"), WINDOW_KEY("main_window") {
    if (mBuilder) {
        mBuilder->get_widget("main_box", mBox);
        mTextArea = Glib::RefPtr<Gtk::TextView>::cast_dynamic(mBuilder->get_object("text_area"));

        // Get textbuffer from textview and connect event listeners
        mTextArea->get_buffer()->signal_changed().connect(sigc::mem_fun(this, &MainWindow::onTextChanged));

        // Load File menu items and connect respectives signal handlers
        mMenuItem_new = Glib::RefPtr<Gtk::MenuItem>::cast_dynamic(mBuilder->get_object("new_submenu_item"));
        mMenuItem_new->signal_activate().connect(sigc::mem_fun(this, &MainWindow::onActivateMenuItem_new));

        mMenuItem_open = Glib::RefPtr<Gtk::MenuItem>::cast_dynamic(mBuilder->get_object("open_submenu_item"));
        mMenuItem_open->signal_activate().connect(sigc::mem_fun(this, &MainWindow::onActivateMenuItem_open));

        mMenuItem_save = Glib::RefPtr<Gtk::MenuItem>::cast_dynamic(mBuilder->get_object("save_submenu_item"));
        mMenuItem_save->signal_activate().connect(sigc::mem_fun(this, &MainWindow::onActivateMenuItem_save));

        mMenuItem_saveAs = Glib::RefPtr<Gtk::MenuItem>::cast_dynamic(mBuilder->get_object("save_as_submenu_item"));
        mMenuItem_saveAs->signal_activate().connect(sigc::mem_fun(this, &MainWindow::onActivateMenuItem_saveAs));

        mMenuItem_quit = Glib::RefPtr<Gtk::MenuItem>::cast_dynamic(mBuilder->get_object("quit_submenu_item"));
        mMenuItem_quit->signal_activate().connect(sigc::mem_fun(this, &MainWindow::onActivateMenuItem_quit));

        // Load Help menu items and connect respectives signal handlers        
        mMenuItem_about = Glib::RefPtr<Gtk::MenuItem>::cast_dynamic(mBuilder->get_object("about_submenu_item"));
        mMenuItem_about->signal_activate().connect(sigc::mem_fun(this, &MainWindow::onActivateMenuItem_about));

        // Add root widget
        add(*mBox);

        // Window properties
        set_title(WINDOW_TITLE);
        set_default_size(800, 600);
        set_border_width(3);
        set_position(Gtk::WIN_POS_CENTER);
    }
}

MainWindow::~MainWindow() {
    delete mBox;
}

// Event Handlers


// File menu items handlers
// TODO
void MainWindow::onActivateMenuItem_new() {
    Application *app = Application::getInstance();
    if (app->getChangesSaved() == false) {
        // Display confirm exit window and wait for input
    }

    // Erase the text area
    mTextArea->get_buffer()->erase(mTextArea->get_buffer()->begin(), mTextArea->get_buffer()->end());
}

void MainWindow::onActivateMenuItem_open() {
    std::cout << "MenuItem Open activated" << std::endl;
}

// TODO
void MainWindow::onActivateMenuItem_save() {
    std::cout << "MenuItem Save activated" << std::endl;
    Application *app = Application::getInstance();
    app->setSaved();
}

// TODO
void MainWindow::onActivateMenuItem_saveAs() {
    std::cout << "MenuItem Save As activated" << std::endl;
}

// TODO
void MainWindow::onActivateMenuItem_quit() {
    Application *app = Application::getInstance();
    if (app->getChangesSaved() == false) {
        std::cout << "changes not saved" << std::endl;
    }
    this->destroy_();
}

// Help menu items handlers
// TODO
void MainWindow::onActivateMenuItem_about() {
    std::cout << "MenuItem About activated" << std::endl;
}

// Changes in the text area
void MainWindow::onTextChanged() {
    Application *app = Application::getInstance();
    app->setUnsaved();
}