#include "result_ag.h"
#include "ui_result_ag.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include "mainwin.h"
using namespace std;

Result_AG::Result_AG(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Result_AG)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,150);





}

void Result_AG::DureeT()
{
    ifstream Duree;
    Duree.open("/home/koopa/duree.txt");
    char row[512]="";
Duree.getline(row,512,'\n');
ui->lineEdit->setText(row);
Duree.getline(row,512,'\n');
ui->lineEdit_2->setText(row);
Duree.close();
}

void Result_AG::remplissage()
{
    ui->tableWidget->setRowCount(nbr_ligne+1);
    std::string numberTemp = std::to_string(0),chaineTemp="";

for (int i=0;i<nbr_ligne;i++)
{
    chaineTemp="Génération ";
    chaineTemp.append(std::to_string(i));
    ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(chaineTemp)));
    ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(tableau[0][i]))));
    ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(tableau[1][i]))));
}

}

Result_AG::~Result_AG()
{
    delete ui;
}

int Result_AG::getNbrLigne()
{
    return nbr_ligne;
}

void Result_AG::setNbrLigne(int n)
{
    this->nbr_ligne=n;
}


//void Result_AG::setTableau(int i,int j,int n)
//{
//    tableau[i][j]=n;
//}
void Result_AG::setTableau(int i,int j,int n)
{
    ui->tableWidget->setItem(j, i+1, new QTableWidgetItem(QString::fromStdString(std::to_string(n))));
}
void Result_AG::setTableauGen(int i,int j,int n)
{
//    ui->tableWidget_2->setItem(i,j, new QTableWidgetItem(QString::fromStdString(std::to_string(n))));
    ui->tableWidget_2->setItem(i, j, new QTableWidgetItem(QString::fromStdString(std::to_string(n))));

}

int Result_AG::getTableau(int i,int j)
{
    return tableau[i][j];
}

void Result_AG::InitTab()
{
    tableau = new int*[3];
    tableau[0] = new  int[nbr_ligne];
    tableau[1] = new  int[nbr_ligne];
    ui->tableWidget->setRowCount(nbr_ligne+1);
for (int i=0;i<=nbr_ligne;i++)
{
    std::string chaineTemp="Génération ";
    chaineTemp.append(std::to_string(nbr_ligne-i));
    ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(chaineTemp)));
}

}


void Result_AG::majtab(int n)
{
    ui->tableWidget_2->setRowCount(n);
}



void Result_AG::on_buttonBox_accepted()
{
    this->hide();
    MainWin *fen = new MainWin();
    fen->show();
}
