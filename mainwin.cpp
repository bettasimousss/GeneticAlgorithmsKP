#include "mainwin.h"
#include <QtWidgets>
#include <QString>
#include "objet.h"
#include "KnackSack.h"
#include "dialog.h"
#include "fichier_pas.h"
#include "exact_choices.h"
#include "wintabou.h"

MainWin::MainWin()
{
    createMenu();
    createMainLayouts();
    createRadioButtons();

//    connect(buttons[0], SIGNAL(clicked()), this, SLOT(sadFichier()));
//    connect(buttons[1], SIGNAL(clicked()), this, SLOT(sadAleatoire()));
//    connect(buttons[2], SIGNAL(clicked()), this, SLOT(sadManuel()));
//    connect(buttons[3], SIGNAL(clicked()), this, SLOT(aide()));

    connect(buttons[0], SIGNAL(clicked()), this, SLOT(sadExact()));
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(sadGenetique()));
    connect(buttons[2], SIGNAL(clicked()), this, SLOT(sadSpecifique()));
    connect(buttons[3], SIGNAL(clicked()), this, SLOT(sadTabou()));
    connect(buttons[4], SIGNAL(clicked()), this, SLOT(aide()));



    //connect(meth_heur_spec, SIGNAL(clicked()), this, SLOT(lancerSAD()));
    connect(meth_larg, SIGNAL(clicked()), this, SLOT(lancerSAD()));
    connect(meth_prof, SIGNAL(clicked()), this, SLOT(lancerSAD()));
    connect(meth_prio, SIGNAL(clicked()), this, SLOT(lancerSAD()));

}
void MainWin::getMethod(){

    if (meth_prof->isChecked()) methode = 0;
    //if(meth_heur_spec->isChecked()) methode = 1;
    if (meth_larg->isChecked()) methode = 2;
    if (meth_prio->isChecked()) methode =2;

}

void MainWin::createMainLayouts(){

    QFormLayout *layout = new QFormLayout;

//    QString titres [4]={"A partir d'un fichier",
//                      "Générer les données aléatoirement",
//                      "Saisir données manuellement",
//                       "Aide"};


    QString titres [5]={"Branch And Bound",
                      "Algorithme Génétique",
                        "Heuristique Spécifique","Recherche Tabou",
                       "Aide"};


//    QString titres [4]={"Méthode Exacte",
//                      "Algorithme Génétique",
//                       "Aide"};
    QLabel *spacer =new QLabel("Résolution du problème du Sac à Dos");
    spacer->setFixedHeight(80);
    spacer->setStyleSheet("font-family:Verdana");
    layout->addRow(spacer);
    layout->setAlignment(spacer,Qt::AlignCenter);

    for(int i=0;i<5;i++){
        if(i==3){
            QLabel *label=new QLabel;
            label->setFixedHeight(20);
            layout->addRow(label);
        }
        buttons[i] = new QPushButton(this);
        buttons[i]->setText(titres[i]);
        buttons[i]->setStyleSheet("color:black; font-family:Verdana;background:#f8f8f8");
        buttons[i]->setFixedSize(300,50);
        layout->addRow(buttons[i]);
        layout->setAlignment(buttons[i],Qt::AlignCenter);
    }

    QGroupBox *formGroupBox = new QGroupBox();
    formGroupBox->setLayout(layout);

    this->layout()->addWidget(formGroupBox);
    this->setFixedWidth(formGroupBox->width());
    this->setFixedHeight(formGroupBox->height());

}

void MainWin::createRadioButtons(){

    choix_meth = new QGroupBox("Quelle stratégie de parcours ?");

    //meth_heur_spec = new QRadioButton("Plus à gauche");
    meth_larg = new QRadioButton("Largeur d'abord");
    meth_prof = new QRadioButton("Profondeur d'abord");
    meth_prio = new QRadioButton("Meilleur d'abord");

   //meth_heur_spec->setChecked(true);
    QVBoxLayout *vbox = new QVBoxLayout;
    //vbox->addWidget(meth_heur_spec);
    vbox->addWidget(meth_larg);
    vbox->addWidget(meth_prof);
    vbox->addWidget(meth_prio);
    vbox->addStretch(1);
    choix_meth->setLayout(vbox);


    QFormLayout *layout = new QFormLayout;
    layout->addRow(choix_meth);
    layout->setAlignment(choix_meth,Qt::AlignCenter);

    methode_dialog = new QDialog;
    methode_dialog->setLayout(layout);
    methode_dialog->setFixedWidth(choix_meth->width()*0.5);

}

void MainWin::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu("&Fichier", this);
    helpMenu = new QMenu("&Aide", this);

    exitAction = new QAction("E&xit",this);
    helpAction = new QAction("A&ide",this) ;
    aboutAction = new QAction ("A p&ropos",this);

    fileMenu->addAction(exitAction);
    helpMenu->addAction(helpAction);
    helpMenu->addAction(aboutAction);


    menuBar->addMenu(fileMenu);
    menuBar->addMenu(helpMenu);

    this->setMenuBar(menuBar);


    //connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(aide()));

}

void MainWin::aide(){
    QMessageBox::information(this, "Aide", "Le fichier en entrée doit suivre le format suivant : \n•Begin data, on peut insérer les informations qu'on veut avant Begin Data\n•Nombres d'objets\n•Volume Maximal\n•Volume minimal\n•End of data" );
}

void MainWin::sadFichier(){
    cheminFichier=QFileDialog::getOpenFileName(this,"Ouvrir un fichier",QString(),
                    "Fichiers(*.txt *.doc *.docx )");

    if(!cheminFichier.isEmpty())
    {
         std::string  path =cheminFichier.toStdString();
        char * chemin=new char [1000] ;
        std::copy(path.begin(),path.end(),chemin);
        chemin[path.length()]='\0';
        init_tableau(chemin);
        tri_tableau();
       methode_dialog->show();
    }




}
void MainWin::sadExact()
    {
    this->hide();
    exact_choices *fen = new exact_choices(this) ;
            fen->show();
    }
void MainWin::sadTabou()
    {
    this->hide();
    WinTabou *fen = new WinTabou(this) ;
            fen->show();
    }
void MainWin::sadGenetique()
    {
    this->hide();
    fichier_pas *fen = new fichier_pas(this) ;
            fen->show();
    }
void MainWin::sadSpecifique()
{
    cheminFichier=QFileDialog::getOpenFileName(this,"Ouvrir un fichier",QString(),
                    "Fichiers(*.txt *.doc *.docx )");

    if(!cheminFichier.isEmpty())
    {
         std::string  path =cheminFichier.toStdString();
        char * chemin=new char [1000] ;
        std::copy(path.begin(),path.end(),chemin);
        chemin[path.length()]='\0';
        init_tableau(chemin);
        tri_tableau();
        this->hide();
resolution(1);
showResults();
    }

}

void MainWin::lancerSAD(){
    methode_dialog->hide();
    getMethod();
    resolution(methode);
    showResults();
}

void MainWin::showResults(){
    this->hide();

        // appliquer l'algo sur listeObj
        // ensuite afficher les résultats sur

        QFormLayout *layout = new QFormLayout;
        QLabel *spacer =new QLabel;
        spacer->setFixedHeight(40);
        layout->addRow(spacer);
        layout->addRow(new QLabel("Résulats de SAD "));
        QPlainTextEdit *textEdit =new QPlainTextEdit();
        textEdit->setReadOnly(true);

        std::ifstream fichier("/home/koopa/trace.txt", std::ios::in);
        QString  qstr;
        if(fichier)
        {
            std::string contenu;
            while(std::getline(fichier, contenu)){
                qstr.append(QString::fromStdString(contenu));
                qstr.append("\n");
            }
            fichier.close();
        }
        else qstr="vide";

        textEdit->appendPlainText(qstr);
        textEdit->setStyleSheet("background:#FFFFFF; color: black;font-family: Verdana;");



        QGroupBox *formGroupBox = new QGroupBox();
        formGroupBox->setLayout(layout);

        winRes =new QMainWindow(this);
        QScrollArea *scrollArea= new QScrollArea;
        scrollArea->setWidgetResizable(1);
        scrollArea->setFixedHeight(250);

        scrollArea->setWidget(textEdit);
        layout->addRow(scrollArea);

        QPushButton *back=new QPushButton("Retour");
        back->setFixedSize(180,40);
        connect(back, SIGNAL(clicked()), this, SLOT(retour()));


        layout->addRow(back);
        layout->setAlignment(back,Qt::AlignCenter);


        winRes->layout()->setMenuBar(menuBar);
        winRes->layout()->addWidget(formGroupBox);
        winRes->setFixedWidth(formGroupBox->width());
        winRes->setFixedHeight(formGroupBox->height());
        winRes->show();

}

void MainWin::sadAleatoire(){
    this->hide();
    Dialog *fenAleatoire = new Dialog(this) ;
            fenAleatoire->show();

}

void MainWin::sadManuel(){
    this->hide();

    QFormLayout *layout = new QFormLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;
    QFormLayout *vlayout = new QFormLayout;


    QLabel *spacer =new QLabel;

    spacer->setFixedHeight(20);
    layout->addRow(spacer);
    winManuel =new QMainWindow(this);
    QGroupBox *formGroupBox = new QGroupBox();
    formGroupBox->setLayout(layout);

    nbObj=new QSpinBox(winManuel);
    nbObj->setMaximum(1000);
    capacite =new QSpinBox(winManuel);
    capacite->setMaximum(1000);


    QLabel *header= new QLabel("Veuillez insérer les paramètres du problème de Sac à Dos  ");
    layout->addRow(header);

    vlayout->addRow(new QLabel("Nombre d'objets:"), nbObj);
    vlayout->addRow(new QLabel("Capacité du Sac à dos:"), capacite);

    QPushButton *okay =new QPushButton("Ok",this);
    okay->setFixedSize(180,35);


    QGroupBox *groupBox = new QGroupBox();

    groupBox->setLayout(vlayout);
    hlayout->addWidget(groupBox);
    hlayout->addWidget(okay);
    layout->addRow(hlayout);


    table= new QTableWidget(winManuel);
    table->setColumnCount(2);
    table->setRowCount(2);
    QString colTitle [2]= {"Volume","Bénéfice"};
    for(int i=0;i<2;i++){
        table->setColumnWidth(i,formGroupBox->width()/2.13);
        table->setHorizontalHeaderItem(i,new QTableWidgetItem(colTitle[i]));

    }
    layout->addRow(table);

    execute =new QPushButton("Lancer SAD",this);
    execute->setFixedSize(180,35);
    execute->setEnabled(false);

    QHBoxLayout *hbox = new QHBoxLayout;
    QPushButton *retour=new QPushButton("Retour");
    retour->setFixedSize(180,35);

    hbox->addWidget(retour);
    hbox->addWidget(execute);



    layout->addRow(hbox);
    layout->setAlignment(hbox,Qt::AlignCenter);
    layout->setAlignment(execute,Qt::AlignCenter);


    winManuel->layout()->setMenuBar(menuBar);
    winManuel->layout()->addWidget(formGroupBox);
    winManuel->setFixedWidth(formGroupBox->width());
    winManuel->setFixedHeight(formGroupBox->height());
    winManuel->show();

    connect(okay, SIGNAL(clicked()), this, SLOT(resizeTable()));
    connect(retour, SIGNAL(clicked()), this, SLOT(retour()));
    connect(execute, SIGNAL(clicked()), this, SLOT(executer()));

}

void MainWin::resizeTable(){
    table->setRowCount(nbObj->value());
    execute->setEnabled(true);

}

void MainWin::executer(){
    winManuel->hide();
    int vol=0, ben=0;
    int max = 0;
    for(int i = 0; i<table->rowCount();i++){
        if (table->item(i,0)!=NULL && table->item(i,1)!=NULL)
        {

            vol = (int) table->item(i,0)->text().toInt(0,10);
            ben = (int) table->item(i,1)->text().toInt(0,10);
            listeObj.append(new Objet(vol,ben));
            if (max<vol) max= vol;
        }
    }
    std::ofstream f;

    f.open("/home/koopa/save.txt");
    f << "begin data" << endl;
    f << listeObj.size() << endl;
    f << capacite->value()<< endl;
    f << max << endl;
    int a,  b;

    for (int i=0; i<listeObj.size(); i++)
    {
        a=listeObj.at(i)->getVolume();
        b=listeObj.at(i)->getBenefice();
        f <<a << "\t" << b << endl;
    }
    f << "end data";

    f.close();
    init_tableau("/home/koopa/save.txt");
    tri_tableau();
    methode_dialog->show();
}

void MainWin::retour(){
    if(winRes!=NULL && winRes->isVisible()){

        this->show();
        winRes->hide();
    }
   else if(winManuel!=NULL)
      if( winManuel->isVisible())
       {
        this->show();
        winManuel->hide();
    }


}

QDialog* MainWin::getMethodeDialog()
{
    return methode_dialog;
}
