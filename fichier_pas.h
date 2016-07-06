#ifndef FICHIER_PAS_H
#define FICHIER_PAS_H

#include <QDialog>

namespace Ui {
class fichier_pas;
}

class fichier_pas : public QDialog
{
    Q_OBJECT

public:
    explicit fichier_pas(QWidget *parent = 0);
    ~fichier_pas();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_buttonBox_rejected();

    void on_pushButton_3_clicked();

private:
    Ui::fichier_pas *ui;
    QString Benchmark;
};

#endif // FICHIER_PAS_H
