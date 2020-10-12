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
    Implements functions from fileutils header
*/

#include "fileutils.hpp"

#include <fstream>
#include <iostream>

bool FileUtils::write(Glib::ustring path, Glib::ustring filename, Glib::ustring content) {
    Glib::ustring fullPath = path+filename;
    std::ofstream outputFilStream;
    bool res;
    try {
        outputFilStream.open(fullPath);
        if (!outputFilStream) {return false;}
        outputFilStream << content;
        res = true;
    } catch (std::ofstream::failure e) {
        std::cout << e.what() << std::endl;
        res = false;
    }
    outputFilStream.close();
    return res;
}

bool FileUtils::read(Glib::ustring pathToFile, Glib::ustring *dest) {
    std::ifstream inputFileStream;
    bool res;
    try {
        inputFileStream.open(pathToFile);
        if (!inputFileStream) {return false;}
        char temp;
        while (inputFileStream.get(temp)) {
            *dest += temp;
        }
        res = true;
    } catch (std::iostream::failure e) {
        std::cout << e.what() << std::endl;
        res = false;
    }
    inputFileStream.close();
    return res;
}
