#ifndef FEN_AG_H
#define FEN_AG_H

#include <QDialog>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <QString>
#include <fstream>
#include "result_ag.h"
namespace Ui {
class Fen_AG;
}

class Fen_AG : public QDialog
{
    Q_OBJECT

public:
    explicit Fen_AG(QWidget *parent = 0);
    void setFen(Result_AG *f);
    Result_AG* getFen();
    ~Fen_AG();

private slots:
    void on_comboBox_4_currentIndexChanged(int index);

    void on_comboBox_5_currentIndexChanged(int index);

    void on_buttonBox_accepted();

    void on_radioButton_clicked(bool checked);

    void on_radioButton_2_clicked(bool checked);

    void on_radioButton_3_clicked(bool checked);

    void on_buttonBox_rejected();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Fen_AG *ui;
    Result_AG *fen;
    QString cheminFichier;
    char* chemin;
};

#endif // FEN_AG_H
