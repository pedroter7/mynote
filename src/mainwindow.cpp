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

#include <iostream>

MainWindow::MainWindow() : mBuilder(Gtk::Builder::create_from_resource("/mynote/res/mainwindow_layout.glade")), openFilePath(""), openFileName(""), WINDOW_TITLE("MyNote"), WINDOW_KEY("main_window") {
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

// Event Handlers

// Create and run a Gtk::MessageDialog and return its return value
int MainWindow::messageDialog(Glib::ustring title, Glib::ustring message) {
    Gtk::MessageDialog messageDialog(message);
    messageDialog.set_title(title);
    return messageDialog.run();
}

// Create a window that asks for user if she wants to save changes
// Return: 0 for save, 1 for discart, 2 for cancel
int MainWindow::confirmExitDialog(bool cancelButton) {
    Gtk::MessageDialog messageDialog("There are unsaved changes, what would you like to do?",false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_NONE);
    messageDialog.set_title("Confirm exit?");
    messageDialog.add_button("Save", 0);
    messageDialog.add_button("Discart", 1);
    if (cancelButton) messageDialog.add_button("Cancel", 2);
    return messageDialog.run();
}



// Returns the window to initial state
void MainWindow::clearWindow() {
    // Erase the text
    Glib::RefPtr<Gtk::TextBuffer> textBuffer = mTextArea->get_buffer();
    textBuffer->erase(textBuffer->begin(), textBuffer->end());
    // Erase names
    openFilePath = "";
    openFileName = "";
    // Set saved
    Application::getInstance()->setSaved();
}

void MainWindow::onActivateMenuItem_new() {
    Application *app = Application::getInstance();
    if (app->getChangesSaved() == false) {
        confirmExitRoutine();
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
            confirmExitRoutine();
        }
        Glib::ustring filename = fChooserDialog.get_filename();
        if (!openRoutine(filename)) {
            messageDialog("Error!", "Some error occured while trying to open the requested file.");
        }
    }
}

void MainWindow::onActivateMenuItem_save() {
    if (openFileName.empty()) {
        Gtk::FileChooserDialog fChooserDialog("Save file");
        fChooserDialog.set_action(Gtk::FILE_CHOOSER_ACTION_SAVE);
        fChooserDialog.add_button("Save", 0);
        fChooserDialog.add_button("Cancel", 1);
        int choice = fChooserDialog.run();
        if (choice == 0) {
            Glib::ustring fullPath = fChooserDialog.get_filename();
            Glib::ustring filename = fullPath.substr(fullPath.find_last_of("/")+1, fullPath.length());
            Glib::ustring path = fullPath.substr(0, fullPath.find_last_of("/")+1);
            if (!saveRoutine(path, filename)) {
                messageDialog("Error!", "Some error occurred while trying to save current file to the requested directory. Be sure that you have permission to do so.");
                onActivateMenuItem_save();
            } else {
                // Set openFileName and openFilePath
                openFileName = filename;
                openFilePath = path;
            }            
        }        
    } else {
        this->saveRoutine(openFilePath, openFileName);
    }
    
}


void MainWindow::onActivateMenuItem_saveAs() {
    Gtk::FileChooserDialog fChooserDialog("Save file");
        fChooserDialog.set_action(Gtk::FILE_CHOOSER_ACTION_SAVE);
        fChooserDialog.add_button("Save", 0);
        fChooserDialog.add_button("Cancel", 1);
        int choice = fChooserDialog.run();
        if (choice == 0) {
            Glib::ustring fullPath = fChooserDialog.get_filename();
            Glib::ustring filename = fullPath.substr(fullPath.find_last_of("/")+1, fullPath.length());
            Glib::ustring path = fullPath.substr(0, fullPath.find_last_of("/")+1);
            if (!saveRoutine(path, filename)) {
                messageDialog("Error!", "Some error occurred while trying to save current file to the requested directory. Be sure that you have permission to do so.");
                onActivateMenuItem_saveAs();
            } else {
                // Set openFileName and openFilePath
                openFileName = filename;
                openFilePath = path;
            }
        }
}


void MainWindow::onActivateMenuItem_quit() {
    onDestroy(nullptr);
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

// Return the choice
int MainWindow::confirmExitRoutine(bool cancelButton){
    int choice = confirmExitDialog(cancelButton); // 0 save, 1 discart, 2 cancel
    switch (choice) {
    case 0: // Save
        onActivateMenuItem_save();
    case 1: // Discart
        clearWindow();
        break;
    case 2: // Cancel
        break;
    }
    return choice;
}

bool MainWindow::saveRoutine(Glib::ustring path, Glib::ustring filename) {
    Glib::RefPtr<Gtk::TextBuffer> textBuffer = mTextArea->get_buffer();
    Glib::ustring content = textBuffer->get_text();
    bool res = FileUtils::write(path, filename, content);
    std::cout << res << std::endl;
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

// Handle when user clicks that X button
bool MainWindow::onDestroy(GdkEventAny* event) {
    Application *app = Application::getInstance();
    if (!app->getChangesSaved()) {
        confirmExitRoutine(false);
    }
    this->destroy_();
    return true;
}