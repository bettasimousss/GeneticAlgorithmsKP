#ifndef WINTABOU_H
#define WINTABOU_H

#include <QDialog>


namespace Ui {
class WinTabou;
}

class WinTabou : public QDialog
{
    Q_OBJECT

public:
    explicit WinTabou(QWidget *parent = 0);
    ~WinTabou();

private slots:
    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pushButton_clicked();

private:
    Ui::WinTabou *ui;
    QString cheminFichier;

};

#endif // WINTABOU_H
