#include "exact_choices.h"
#include "ui_exact_choices.h"
#include "KnackSack.h"
exact_choices::exact_choices(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exact_choices)
{
    ui->setupUi(this);
}

exact_choices::~exact_choices()
{
    delete ui;
}

void exact_choices::on_pushButton_clicked()
{
this->hide();
mainwin = new MainWin();
mainwin->sadManuel();


}

void exact_choices::on_pushButton_2_clicked()
{
    mainwin = new MainWin();
mainwin->sadFichier();
        this->hide();

}

void exact_choices::on_pushButton_3_clicked()
{
    this->hide();
    mainwin = new MainWin();
    mainwin->sadAleatoire();
}

void exact_choices::on_buttonBox_rejected()
{
MainWin *fen = new MainWin();
fen->show();
this->hide();
}
