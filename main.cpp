#include "chifoumivue.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChifoumiVue w;
    w.show();
    return a.exec();
}
