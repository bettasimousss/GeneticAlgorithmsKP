#ifndef DIALOG_2_H
#define DIALOG_2_H

#include <QDialog>

namespace Ui {
class Dialog_2;
}

class Dialog_2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_2(QWidget *parent = 0);
    ~Dialog_2();

private:
    Ui::Dialog_2 *ui;
};

#endif // DIALOG_2_H
