#include "fen_ag.h"
#include "ui_fen_ag.h"
#include <iostream>
#include "strategies.h"
#include "mainwin.h"
using namespace std;

Fen_AG::Fen_AG(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Fen_AG)
{
    ui->setupUi(this);
    ui->doubleSpinBox_7->setSingleStep(0.1);
    ui->doubleSpinBox_8->setSingleStep(0.1);
    ui->doubleSpinBox_9->setSingleStep(0.1);
    ui->doubleSpinBox_10->setSingleStep(0.1);
    ui->doubleSpinBox_11->setSingleStep(0.1);
    ui->doubleSpinBox_13->setSingleStep(0.1);

    ui->doubleSpinBox_7->setValue(0.7);
    ui->doubleSpinBox_9->setValue(0.8);
    ui->doubleSpinBox_8->setValue(0.1);
    ui->doubleSpinBox_13->setValue(0.02);





}

Fen_AG::~Fen_AG()
{
    delete ui;
}



void Fen_AG::on_comboBox_4_currentIndexChanged(int index)
{
    if (index == 0 )
    {
        ui->spinBox_2->setEnabled(true);
        ui->doubleSpinBox_10->setEnabled(false);
        ui->doubleSpinBox_11->setEnabled(false);

    }
    if (index == 1 )
    {
        ui->spinBox_2->setEnabled(false);
        ui->doubleSpinBox_10->setEnabled(true);
        ui->doubleSpinBox_11->setEnabled(false);

    }
    if (index == 2)
    {
        ui->spinBox_2->setEnabled(false);
        ui->doubleSpinBox_10->setEnabled(false);
        ui->doubleSpinBox_11->setEnabled(true);

    }
}

void Fen_AG::on_comboBox_5_currentIndexChanged(int index)
{
    if (index == 2)
    {
        ui->spinBox_3->setEnabled(true);
    }
    else {
        ui->spinBox_3->setEnabled(false);

    }
}

void Fen_AG::on_buttonBox_accepted()
{

    std::ofstream f;
    f.open("/home/koopa/param2.txt");
    f << "begin data" << endl;
f<< ui->spinBox->value()<<endl;
int index = ui->comboBox_5->currentIndex();
switch (index){
case 0 :
    f<< "a"<<endl;break;
case 1 :
        f<< "g"<<endl;break;
case 2 :
        f<< "m("<<ui->spinBox_3->value()<<")"<<endl;break;
}
f<<ui->doubleSpinBox_7->value()<<endl;
f<<ui->doubleSpinBox_9->value()<<endl;
f<<ui->doubleSpinBox_8->value()<<endl;
index = ui->comboBox->currentIndex();


switch(index){
case 0 :
    f<< "a"<<endl;break;
case 1 :
        f<< "e"<<endl;break;
case 2 :
        f<< "r"<<endl;break;
}
index = ui->comboBox_6->currentIndex();


switch(index){
case 0 :
    f<< "e"<<endl;break;
case 1 :
        f<< "m"<<endl;break;
case 2 :
        f<< "g"<<endl;break;
}


index = ui->comboBox_2->currentIndex();


switch(index){
case 0 :
    f<< "a"<<endl;break;
case 1 :
        f<< "d"<<endl;break;
case 2 :
        f<< "e"<<endl;break;
}

index = ui->comboBox_3->currentIndex();


//hna
switch(index){
case 0 :
    f<< "1"<<endl;break;
case 1 :
        f<< "2"<<endl;break;
}

index = ui->comboBox_4->currentIndex();


//hna
switch(index){
case 0 :
    f<< "i"<<endl;break;
case 1 :
        f<< "e"<<endl;break;
case 2 :
        f<< "s"<<endl;break;
}


f<<ui->spinBox_2->value()<<endl;
f<<ui->doubleSpinBox_10->value()<<endl;
f<<ui->doubleSpinBox_11->value()<<endl;
f<<ui->doubleSpinBox_13->value()<<endl<<"end data";
f.close();
recup_AGparam("/home/koopa/param2.txt");
init_tableau_strategie(chemin);
tri_tableau_strategie();
//fichier csv output matensahche

srand(time(NULL));
cout<<"mon adresse est "<<this<<endl;
AG(param,"D:\\param.txt",this);

}

void Fen_AG::on_radioButton_clicked(bool checked)
{
    if (checked ){
    ui->comboBox_5->setCurrentIndex(1);
    ui->comboBox->setCurrentIndex(1);
    ui->comboBox_3->setCurrentIndex(1);
    ui->comboBox_6->setCurrentIndex(0);
    ui->comboBox_4->setCurrentIndex(2);
    ui->comboBox_2->setCurrentIndex(1);


    }


}

void Fen_AG::on_radioButton_2_clicked(bool checked)
{
    if (checked ){
        ui->comboBox_5->setCurrentIndex(0);
        ui->comboBox->setCurrentIndex(0);
        ui->comboBox_3->setCurrentIndex(0);
        ui->comboBox_6->setCurrentIndex(2);
        ui->comboBox_4->setCurrentIndex(0);
        ui->comboBox_2->setCurrentIndex(2);

    }
}

void Fen_AG::on_radioButton_3_clicked(bool checked)
{
    if (checked ){
        ui->comboBox_5->setCurrentIndex(0);
        ui->comboBox->setCurrentIndex(2);
        ui->comboBox_3->setCurrentIndex(1);
        ui->comboBox_6->setCurrentIndex(1);
        ui->comboBox_4->setCurrentIndex(0);
        ui->comboBox_2->setCurrentIndex(2);

    }
}

void Fen_AG::on_buttonBox_rejected()
{
    MainWin *fen = new MainWin();
    fen->show();
    this->hide();
}


void Fen_AG::setFen(Result_AG *f){
    fen=f;
}

Result_AG* Fen_AG::getFen(){
return fen;
}

void Fen_AG::on_pushButton_clicked()
{
    cheminFichier=QFileDialog::getOpenFileName(this,"Ouvrir un fichier",QString(),
                    "Fichiers(*.txt *.doc *.docx )");

    if(!cheminFichier.isEmpty())
    {
         std::string  path =cheminFichier.toStdString();
       chemin=new char [1000] ;
        std::copy(path.begin(),path.end(),chemin);
        chemin[path.length()]='\0';
    }
}

void Fen_AG::on_pushButton_2_clicked()
{
    QString cheminFichier2=QFileDialog::getOpenFileName(this,"Ouvrir un fichier",QString(),
                    "Fichiers(*.txt *.doc *.docx )");
    if(!cheminFichier2.isEmpty())
    {
         std::string  path =cheminFichier2.toStdString();
       char* chemin2=new char [1000] ;
        std::copy(path.begin(),path.end(),chemin2);
        chemin2[path.length()]='\0';
        ifstream f;
        int entier;
        float flottant;
        f.open(chemin2);
        char row[512]="";
        bool found_begin=false,eof=false,endofdata=false;

        int i=0;
        if(f.is_open())
            {
            while(!found_begin && !eof)
                    {
                f.getline(row,512,'\n');
                if(strcmp(row,"begin data\r")==0 ) {
                               found_begin=true;
                           }
                if(f.eof()) eof=true;
            }
            if(found_begin)
                    {
                f.getline(row,512,'\n');
entier=atoi(row);
ui->spinBox->setValue(entier);
f.getline(row,512,'\n');
char caractere=row[0];
switch (caractere)
{
case 'a' :
    ui->comboBox_5->setCurrentIndex(0);break;
case 'g' :
    ui->comboBox_5->setCurrentIndex(1);break;
case 'm' :
    ui->comboBox_5->setCurrentIndex(2);

    break;

}
f.getline(row,512,'\n');
flottant=(float)atof(row);
ui->doubleSpinBox_7->setValue(flottant);
f.getline(row,512,'\n');
flottant=(float)atof(row);
ui->doubleSpinBox_9->setValue(flottant);
f.getline(row,512,'\n');
flottant=(float)atof(row);
ui->doubleSpinBox_8->setValue(flottant);
f.getline(row,512,'\n');
caractere=row[0];
switch (caractere)
{
case 'a' :
    ui->comboBox->setCurrentIndex(0);break;
case 'e' :
    ui->comboBox->setCurrentIndex(1);break;
case 'r' :
    ui->comboBox->setCurrentIndex(2);

    break;

}
f.getline(row,512,'\n');
caractere=row[0];
switch (caractere)
{
case 'e' :
    ui->comboBox_6->setCurrentIndex(0);break;
case 'm' :
    ui->comboBox_6->setCurrentIndex(1);break;
case 'g' :
    ui->comboBox_6->setCurrentIndex(2);

    break;

}
f.getline(row,512,'\n');
caractere=row[0];
switch (caractere)
{
case 'd' :
    ui->comboBox_2->setCurrentIndex(0);break;
case 'a' :
    ui->comboBox_2->setCurrentIndex(1);break;
case 'e' :
    ui->comboBox_2->setCurrentIndex(2);

    break;

}
f.getline(row,512,'\n');
caractere=row[0];
switch (caractere)
{
case '1' :
    ui->comboBox_3->setCurrentIndex(0);break;
case '2' :
    ui->comboBox_3->setCurrentIndex(1);break;
}
f.getline(row,512,'\n');
caractere=row[0];
switch (caractere)
{
case 'i' :
    ui->comboBox_4->setCurrentIndex(0);break;
case 's' :
    ui->comboBox_4->setCurrentIndex(1);break;
case 'e' :
    ui->comboBox_4->setCurrentIndex(2);
    break;
}
f.getline(row,512,'\n');
flottant=(float)atof(row);
ui->spinBox_2->setValue(flottant);
f.getline(row,512,'\n');
flottant=(float)atof(row);
ui->doubleSpinBox_10->setValue(flottant);
f.getline(row,512,'\n');
flottant=(float)atof(row);
ui->doubleSpinBox_11->setValue(flottant);
f.getline(row,512,'\n');
flottant=(float)atof(row);
ui->doubleSpinBox_13->setValue(flottant);
f.getline(row,512,'\n');
if(strcmp(row,"end data\r")==0 ) {
              found_begin=true;
              if (f.eof()) eof=true;
          }
            }


        }


    }
}
