#include "widget.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    //固定
    w.setFixedSize(1000,1000);
    return a.exec();
}


