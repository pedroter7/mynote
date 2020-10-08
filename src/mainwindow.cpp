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
#include "confirmexitwindow.hpp"
#include "savewindow.hpp"
#include "fileutils.hpp"

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/textview.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/messagedialog.h>

#include <gdkmm/pixbuf.h>

#include <glibmm/refptr.h>

#include <sigc++/sigc++.h>

#include <mutex>
#include <iostream>

MainWindow::MainWindow() : mBuilder(Gtk::Builder::create_from_resource("/mynote/res/mainwindow_layout.glade")), openFilePath(""), openFileName(""), mMutex(), NEW_CLICKED(false), WINDOW_TITLE("MyNote"), WINDOW_KEY("main_window") {
    if (mBuilder) {
        mBuilder->get_widget("main_box", mBox);
        mTextArea = Glib::RefPtr<Gtk::TextView>::cast_dynamic(mBuilder->get_object("text_area"));

        // Get textbuffer from textview and connect event listeners
        Glib::RefPtr<Gtk::TextBuffer> textBuffer = mTextArea->get_buffer();
        textBuffer->signal_changed().connect(sigc::mem_fun(this, &MainWindow::onTextChanged));

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

        // Connect delete event
        this->signal_delete_event().connect(sigc::mem_fun(this, &MainWindow::onDestroy));

        // Add root widget
        add(*mBox);

        // Window properties
        set_title(WINDOW_TITLE);
        set_icon(Gdk::Pixbuf::create_from_resource("/mynote/res/img/mynote_ic_32.png"));
        set_default_size(800, 600);
        set_border_width(3);
        set_position(Gtk::WIN_POS_CENTER);
    }
}

MainWindow::~MainWindow() {
    delete mBox;
}

bool MainWindow::getNewClicked() {return NEW_CLICKED;}

void MainWindow::setNewClicked(bool set) {NEW_CLICKED = set;}

// Event Handlers

// Create and run a Gtk::MessageDialog and return its return value
int MainWindow::messageDialog(Glib::ustring title, Glib::ustring message) {
    Gtk::MessageDialog messageDialog(message);
    messageDialog.set_title(title);
    return messageDialog.run();
}

// Returns the window to initial state
void MainWindow::clearWindow() {
    std::lock_guard<std::mutex> lock(mMutex);
    // Erase the text
    Glib::RefPtr<Gtk::TextBuffer> textBuffer = mTextArea->get_buffer();
    textBuffer->erase(textBuffer->begin(), textBuffer->end());
    // Set saved
    Application::getInstance()->setSaved();
}

// File menu items handlers
// TODO
// void MainWindow::onActivateMenuItem_new() {
//     Application *app = Application::getInstance();
//     if (app->getChangesSaved() == false) {
//         NEW_CLICKED = true;
//         // Display confirm exit window
//         ConfirmExitWindow *tempWindow = new ConfirmExitWindow(this);
//         app->setTemporaryWindow(tempWindow, true);
//         app->addWindow(tempWindow->WINDOW_KEY);
//         app->displayWindow(tempWindow->WINDOW_KEY);
//     } else {
//         clearWindow();
//     }
// }

void MainWindow::onActivateMenuItem_new() {
    Application *app = Application::getInstance();
    if (app->getChangesSaved() == false) {
        Gtk::MessageDialog messageDialog("There are unsaved changes, would you like to save?");
        messageDialog.run();
    } else {
        clearWindow();
    }
}

void MainWindow::onActivateMenuItem_open() {
    Gtk::FileChooserDialog fChooserDialog("Select a file to open");
    fChooserDialog.add_button("Open", 0);
    fChooserDialog.add_button("Cancel", 1);
    int choice = fChooserDialog.run();
    if (choice == 0) {
        Application *app = Application::getInstance();
        if (!app->getChangesSaved()) {
            // display unsaved changes dialog
            std::cout << "UNSAVED CHANGES" << std::endl;
        }
        Glib::ustring filename = fChooserDialog.get_filename();
        if (!openRoutine(filename)) {
            messageDialog("Error!", "Some error occured while trying to open the requested file.");
        }
    }
}

// TODO
void MainWindow::onActivateMenuItem_save() {
    std::lock_guard<std::mutex> lock(mMutex);
    
    Application *app = Application::getInstance();

    if (openFileName.empty()) {
        SaveWindow *tempWindow = new SaveWindow(this);
        app->setTemporaryWindow(tempWindow, true);
        app->addWindow(tempWindow->WINDOW_KEY);
        app->displayWindow(tempWindow->WINDOW_KEY);
    } else {
        this->saveRoutine(openFilePath, openFileName);
    }
    
}

// TODO
void MainWindow::onActivateMenuItem_saveAs() {
    std::lock_guard<std::mutex> lock(mMutex);

    SaveWindow *tempWindow = new SaveWindow(this);
    Application *app = Application::getInstance();
    app->setTemporaryWindow(tempWindow, true);
    app->addWindow(tempWindow->WINDOW_KEY);
    app->displayWindow(tempWindow->WINDOW_KEY);

}

// TODO
void MainWindow::onActivateMenuItem_quit() {
    Application *app = Application::getInstance();
    if (app->getChangesSaved() == false) {
        std::cout << "changes not saved" << std::endl;
    }
    this->destroy_();
}

// Create and run a AboutDialog instance
void MainWindow::onActivateMenuItem_about() {
    Gtk::AboutDialog aboutDialog;
    aboutDialog.set_title("About MyNote");
    aboutDialog.set_program_name("MyNote");
    aboutDialog.set_logo(Gdk::Pixbuf::create_from_resource("/mynote/res/img/mynote_ic_128.png"));
    // Get the content to add to aboutWindow
    auto builder = Gtk::Builder::create_from_resource("/mynote/res/about_dialog_content.glade");
    Gtk::Widget *content = nullptr;
    builder->get_widget("content_box", content);
    // Add the content
    Gtk::Box *box = aboutDialog.get_content_area();
    box->add(*content);    
    aboutDialog.run();
    // Free memory
    delete content;
}

// Changes in the text area
void MainWindow::onTextChanged() {
    Application *app = Application::getInstance();
    app->setUnsaved();
}

// Routines
bool MainWindow::saveRoutine(Glib::ustring path, Glib::ustring filename) {
    Glib::RefPtr<Gtk::TextBuffer> textBuffer = mTextArea->get_buffer();
    Glib::ustring content = textBuffer->get_text();
    bool res = FileUtils::write(path, filename, content);
    if (res) {
        Application *app = Application::getInstance();
        app->setSaved();
    }
    return res;
}

bool MainWindow::openRoutine(Glib::ustring pathToFile) {
    Glib::ustring content;
    bool openFile = FileUtils::read(pathToFile, &content);
    if (openFile) {
        openFileName = pathToFile.substr(pathToFile.find_last_of("/")+1, pathToFile.length()-1);
        openFilePath = pathToFile.erase(pathToFile.find_last_of("/")+1, pathToFile.length()-1);
        Glib::RefPtr<Gtk::TextBuffer> textBuffer = mTextArea->get_buffer();
        textBuffer->erase(textBuffer->begin(), textBuffer->end());
        textBuffer->insert(textBuffer->begin(), content);
        Application *app = Application::getInstance();
        app->setSaved();
        return true;
    } 
    return false;
}

bool MainWindow::onDestroy(GdkEventAny* event) {
    std::cout << "DESTROY" << std::endl;
    this->destroy_();
    return true;
}