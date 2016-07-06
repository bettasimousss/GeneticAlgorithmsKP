#ifndef EXACT_CHOICES_H
#define EXACT_CHOICES_H

#include <QDialog>
#include "mainwin.h"

namespace Ui {
class exact_choices;
}

class exact_choices : public QDialog
{
    Q_OBJECT

public:
    explicit exact_choices(QWidget *parent = 0);
    ~exact_choices();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_buttonBox_rejected();

private:
    Ui::exact_choices *ui;
    MainWin *mainwin;
    int gen;
};

#endif // EXACT_CHOICES_H
