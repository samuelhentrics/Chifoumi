#ifndef PARAMETRAGE_H
#define PARAMETRAGE_H

#include <QDialog>

namespace Ui {
class parametrage;
}

class parametrage : public QDialog
{
    Q_OBJECT

public:
    explicit parametrage(QWidget *parent = nullptr);
    ~parametrage();

private:
    Ui::parametrage *ui;
};

#endif // PARAMETRAGE_H
