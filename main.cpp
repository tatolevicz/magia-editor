#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/resources/fonts/Courier-New.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/Courier-New-Bold.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/Poppins-ExtraBold.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/Poppins-Regular.ttf");

    MainWindow w;
    w.show();
    return a.exec();
}

//
//#include <sol/sol.hpp>
//#include <cassert>
//
//int main() {
//
//    sol::state lua;
//    int x = 0;
//
//    lua.set_function("beep", [&x]{
//        ++x;
//        std::cout << "beep: " << x << std::endl;
//    });
//
//    lua.script("beep()");
//    lua.script("beep()");
//    lua.script("beep()");
//
//    assert(x == 3);
//}