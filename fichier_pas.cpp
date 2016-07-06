#include "fichier_pas.h"
#include "ui_fichier_pas.h"
#include "fen_ag.h"
#include <QDialog>
#include "strategies.h"
#include <QFileDialog>
#include "mainwin.h"
fichier_pas::fichier_pas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fichier_pas)
{
    ui->setupUi(this);
}

fichier_pas::~fichier_pas()
{
    delete ui;
}

void fichier_pas::on_pushButton_clicked()
{

Fen_AG *fen2 = new Fen_AG(this);
fen2->show();
this->hide();
}

void fichier_pas::on_pushButton_2_clicked()
{
    QString cheminFichier=QFileDialog::getOpenFileName(this,"Ouvrir un fichier",QString(),
                    "Fichiers(*.txt *.doc *.docx )");

    if(!cheminFichier.isEmpty() && (!Benchmark.isEmpty()))
    {
         std::string  path =cheminFichier.toStdString();
         std::string  path2 =Benchmark.toStdString();


        char * chemin=new char [1000] ;
        char * chemin2=new char [1000] ;

        std::copy(path.begin(),path.end(),chemin);
        std::copy(path2.begin(),path2.end(),chemin2);

        chemin[path.length()]='\0';
        chemin2[path2.length()]='\0';

        recup_AGparam(chemin,1);
        init_tableau_strategie(chemin2);
        tri_tableau_strategie();
        //fichier csv output matensahche

        srand(time(NULL));
        AG(param,"D:\\param.txt",this);
        this->hide();
//        Fen_AG *fen2 = new Fen_AG(this);
//        fen2->show();
        this->hide();

    }
}

void fichier_pas::on_buttonBox_rejected()
{
    MainWin *fen = new MainWin();
    fen->show();
    this->hide();
}



void fichier_pas::on_pushButton_3_clicked()
{
    Benchmark=QFileDialog::getOpenFileName(this,"Ouvrir un fichier",QString(),
                                           "Fichiers(*.txt *.doc *.docx )");
}
