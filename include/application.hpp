/*
Application is a singleton class that abstracts a Gtk::Application instance for MyNote
and stores the instances for all windows used in the application
*/

#ifndef _MYNOTE_APPLICATION_HPP_
#define _MYNOTE_APPLICATION_HPP_

#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>

#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

#include <map>

class Application {
private:
    Application();

    static Application *uniqueInstance;

    Glib::RefPtr<Gtk::Application> mGtkApplication;

    // Instances of each window
    std::map<Glib::ustring, Gtk::ApplicationWindow*> windows;

public:
    ~Application();
    static Application* getInstance();

    // MyNote app ID, defined in application.cpp: com.github.pedroter7.mynote
    static const Glib::ustring APP_ID;

    // Abstracts a call to Gtk::Application run() method
    int run();

};


#endif // _MYNOTE_APPLICATION_HPP_