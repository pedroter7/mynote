#include "mainwindow.hpp"

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/textview.h>

#include <glibmm/refptr.h>

MainWindow::MainWindow() : mBuilder(Gtk::Builder::create_from_resource("/mynote/res/mainwindow_layout.glade")) {
    if (mBuilder) {
        mBuilder->get_widget("main_box", mBox);
        mTextArea = Glib::RefPtr<Gtk::TextView>::cast_dynamic(mBuilder->get_object("text_area"));

        add(*mBox);

        // Window properties
        set_title("MyNote");
        set_default_size(800, 600);
        set_border_width(3);
        set_position(Gtk::WIN_POS_CENTER);
    }
}

MainWindow::~MainWindow() {
    delete mBox;
}
