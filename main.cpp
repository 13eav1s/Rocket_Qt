#include "mainwindow.h"

#include <QApplication>
//#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication rocket_app(argc, argv);
    MainWindow w;
    w.show();
    return rocket_app.exec();
}
