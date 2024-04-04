#include "jsonapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JsonApp w;
    w.show();

    return a.exec();
}
