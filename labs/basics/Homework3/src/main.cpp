#include <QApplication>
#include "main_window.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("LingoApp");
    w.resize(500, 400);
    w.show();
    return a.exec();
}