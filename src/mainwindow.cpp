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

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/textview.h>
#include <gtkmm/menuitem.h>

#include <glibmm/refptr.h>

#include <sigc++/sigc++.h>

#include <iostream>

MainWindow::MainWindow() : mBuilder(Gtk::Builder::create_from_resource("/mynote/res/mainwindow_layout.glade")), WINDOW_TITLE("MyNote") {
    if (mBuilder) {
        mBuilder->get_widget("main_box", mBox);
        mTextArea = Glib::RefPtr<Gtk::TextView>::cast_dynamic(mBuilder->get_object("text_area"));

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
void MainWindow::onActivateMenuItem_new() {
    std::cout << "MenuItem New activated" << std::endl;
}

void MainWindow::onActivateMenuItem_open() {
    std::cout << "MenuItem Open activated" << std::endl;
}

void MainWindow::onActivateMenuItem_save() {
    std::cout << "MenuItem Save activated" << std::endl;
}

void MainWindow::onActivateMenuItem_saveAs() {
    std::cout << "MenuItem Save As activated" << std::endl;
}

void MainWindow::onActivateMenuItem_quit() {
    std::cout << "MenuItem Quit activated" << std::endl;
}

// Help menu items handlers
void MainWindow::onActivateMenuItem_about() {
    std::cout << "MenuItem About activated" << std::endl;
}