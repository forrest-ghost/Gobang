#include "widget.h"
#include"game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("五子棋");
    w.show();
    return a.exec();
}
