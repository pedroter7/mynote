#ifndef _MYNOTE_MAIN_WINDOW_HPP_
#define _MYNOTE_MAIN_WINDOW_HPP_

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/textview.h>

#include <glibmm/refptr.h>

class MainWindow : public Gtk::ApplicationWindow {
private:
    Gtk::Box *mBox; // Root element of the layout
    Glib::RefPtr<Gtk::Builder> mBuilder;
    Glib::RefPtr<Gtk::TextView> mTextArea;

public:
    MainWindow();
    ~MainWindow();

};

#endif // _MYNOTE_MAIN_WINDOW_HPP_