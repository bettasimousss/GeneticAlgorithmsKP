#ifndef RESULT_TABOU_H
#define RESULT_TABOU_H

#include <QDialog>

namespace Ui {
class Result_Tabou;
}

class Result_Tabou : public QDialog
{
    Q_OBJECT

public:
    explicit Result_Tabou(QWidget *parent = 0);
    void setVolumeCon(int n);
    void setEval(int n);
    void setTableauGen(int i,int j,int n);
    void majtab(int n);




    ~Result_Tabou();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Result_Tabou *ui;
    int eval;
    int volumeCon;

};

#endif // RESULT_TABOU_H
