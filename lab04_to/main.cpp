#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
// file_name: main.cpp
// exec: qmake -project "QT += widgets" && qmake && make && ./nombre_del_ejecutable
