#include "chifoumi.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Chifoumi w;
    w.show();
    return a.exec();
}
