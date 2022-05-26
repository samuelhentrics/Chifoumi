#ifndef PARAMETRAGE_H
#define PARAMETRAGE_H

#include <QDialog>

namespace Ui {
class Parametrage;
}

class Parametrage : public QDialog
{
    Q_OBJECT

public:
    explicit Parametrage(QWidget *parent = nullptr);
    ~Parametrage();
    QString getNom();
    unsigned int getPoints();
    unsigned int getTemps();

private:
    Ui::Parametrage *ui;
};

#endif // PARAMETRAGE_H
