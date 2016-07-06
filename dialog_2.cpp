#include "dialog_2.h"
#include "ui_dialog_2.h"

Dialog_2::Dialog_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_2)
{
    ui->setupUi(this);
}

Dialog_2::~Dialog_2()
{
    delete ui;
}
