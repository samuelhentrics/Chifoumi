#include "connexion.h"
#include "chifoumivue.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChifoumiVue w;
    return a.exec();
}
