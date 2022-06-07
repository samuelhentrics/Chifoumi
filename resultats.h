#ifndef RESULTATS_H
#define RESULTATS_H

#include <QDialog>

namespace Ui {
class resultats;
}

class resultats : public QDialog
{
    Q_OBJECT

public:
    explicit resultats(QWidget *parent = nullptr);
    ~resultats();

private:
    Ui::resultats *ui;
};

#endif // RESULTATS_H
