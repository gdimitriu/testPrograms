#include "maindrawings.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainDrawings w;
    w.show();

    return a.exec();
}
