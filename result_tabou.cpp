#include "result_tabou.h"
#include "ui_result_tabou.h"
#include <QStandardItemModel>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include "mainwin.h"
using namespace std;

Result_Tabou::Result_Tabou(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Result_Tabou)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->setRowCount(1);

    ifstream tabu,tabu2;
    tabu.open("/home/koopa/tabu.txt");
    tabu2.open("/home/koopa/tabu2.txt");

    char row[512]="";
tabu.getline(row,512,'\n');
char row2[512]="";
tabu2.getline(row2,512,'\n');
int nbrLigne = atoi(row2);
ui->tableWidget->setItem(0, 0, new QTableWidgetItem(QString::fromStdString(row)));
tabu.getline(row,512,'\n');
ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(row)));
ui->tableWidget_2->setRowCount(nbrLigne+1);
for(int i= 0;i<=nbrLigne;i++)
{
    tabu.getline(row,512,'\n');
    ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(row)));
    tabu.getline(row,512,'\n');
    ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(row)));
}
tabu.getline(row,512,'\n');
ui->tableWidget->setItem(0, 2, new QTableWidgetItem(QString::fromStdString(row)));
tabu.close();



}

Result_Tabou::~Result_Tabou()
{
    delete ui;
}

void Result_Tabou::setEval(int n)
{
    eval=n;
}


void Result_Tabou::setVolumeCon(int n)
{
    volumeCon=n;
}

void Result_Tabou::on_pushButton_clicked()
{
    this->hide();
    MainWin *fen=new MainWin();
}

void Result_Tabou::majtab(int n)
{
    ui->tableWidget_2->setRowCount(n);
    ui->tableWidget_2->setItem(0, 0, 0);
}

void Result_Tabou::setTableauGen(int i,int j,int n)
{
//    ui->tableWidget_2->setItem(i,j, new QTableWidgetItem(QString::fromStdString(std::to_string(n))));
    ui->tableWidget_2->setItem(i, j, new QTableWidgetItem(QString::fromStdString(std::to_string(n))));

}
