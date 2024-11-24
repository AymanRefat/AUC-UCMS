#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QUuid>
#include "app.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
