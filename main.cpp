#include "mainwindow.h"

#include <QApplication>
#include "widget.h"

//extern int global_variable;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setMinimumSize(200,200);
    w.show();
    return a.exec();
}
