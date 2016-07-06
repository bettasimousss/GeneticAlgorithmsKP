#include "wintabou.h"
#include "ui_wintabou.h"
#include "mainwin.h"
#include "traitement.h"
#include "result_tabou.h"

WinTabou::WinTabou(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinTabou)
{
    ui->setupUi(this);
}

WinTabou::~WinTabou()
{
    delete ui;
}

void WinTabou::on_radioButton_2_clicked()
{
    ui->spinBox->setEnabled(true);
}

void WinTabou::on_radioButton_3_clicked()
{
    ui->spinBox->setEnabled(true);
}

void WinTabou::on_radioButton_clicked()
{
    ui->spinBox->setEnabled(true);
}

//test

void WinTabou::on_buttonBox_accepted()
{
    clock_t begin = clock();
    std::string  path =cheminFichier.toStdString();
   char * chemin=new char [1000] ;
   std::copy(path.begin(),path.end(),chemin);
   chemin[path.length()]='\0';
    recup_data_traitement(chemin);
        tri_tableau_traitement();
        solution s;
        int nb; // nombre d'iteration maximale pour generer un meilleure voisin ou le 1 er meilleure voisin


        s=init_solution(s);

        s=LM_Branch_traitement(s);
        maxsize_tabulist=ui->spinBox_2->value();


if (ui->radioButton->isChecked())
{
    s=tabuSearchRandom(s,ui->spinBox->value(),ui->spinBox->value());
}
else if (ui->radioButton_2->isChecked() ){
        s=tabuSearchBest(s,ui->spinBox_5->value(),ui->spinBox->value());}
else if (ui->radioButton_3->isChecked() ){
        s=tabuSearchFirst(s,ui->spinBox->value(),ui->spinBox->value());
}
this->hide();
clock_t end = clock();
double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
ofstream tabu;
tabu.open("/home/koopa/tabu.txt",std::ios_base::app);
tabu<<elapsed_secs;
tabu.close();



Result_Tabou *fen= new Result_Tabou(this);
fen->show();
}

void WinTabou::on_buttonBox_rejected()
{
    MainWin *fen = new MainWin();
    fen->show();
    this->hide();
}

void WinTabou::on_pushButton_clicked()
{
    cheminFichier=QFileDialog::getOpenFileName(this,"Ouvrir un fichier",QString(),
                                                "Fichiers(*.txt *.doc *.docx )");
}
