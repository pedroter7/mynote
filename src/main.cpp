/*
Startpoint for MyNote application
*/

#include "application.hpp"

int main(int argc, char *argv[]) {
    Application *appInstance = Application::getInstance();
    int result = appInstance->run();
    return result;
}
