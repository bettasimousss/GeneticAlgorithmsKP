#ifndef RESULT_AG_H
#define RESULT_AG_H

#include <QDialog>

namespace Ui {
class Result_AG;
}

class Result_AG : public QDialog
{
    Q_OBJECT

public:
    explicit Result_AG(QWidget *parent = 0);
    int getTableau(int i,int j);
    int getNbrLigne();
    void setNbrLigne(int n);
    void setTableau(int i,int j,int n) ;
    void InitTab();
    void remplissage();
    void setTemps(int n);
    void DureeT();
    void setTableauGen(int i,int j,int n);
    void majtab(int n);




    ~Result_AG();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Result_AG *ui;
    int** tableau;
    int nbr_ligne;
    int temps;
};

#endif // RESULT_AG_H
