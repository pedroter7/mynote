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
    This is a classic confirm exit window that asks if the user wants to save changes or not
*/

#ifndef _MYNOTE_CONFIRM_EXIT_WINDOW_HPP_
#define _MYNOTE_CONFIRM_EXIT_WINDOW_HPP_

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>

#include <glibmm/refptr.h>

class ConfirmExitWindow : public Gtk::ApplicationWindow {};

#endif // _MYNOTE_CONFIRM_EXIT_WINDOW_HPP_