#include "dialog.h"
#include "ui_dialog.h"
#include "objet.h"
#include "KnackSack.h"
#include "mainwin.h"
#include <QtWidgets>
#include <QString>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;

}

void Dialog::on_pushButton_clicked()
{
    generate_instance("/home/koopa/save.txt",ui->spinBox->value(),ui->spinBox_2->value() , ui->spinBox_3->value(), ui->spinBox_4->value(), ui->spinBox_5->value());
int c=5;
    init_tableau("/home/koopa/save.txt");
tri_tableau();
    MainWin *fen = new MainWin();
    fen->getMethodeDialog()->show();
    this->hide();

}
