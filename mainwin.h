#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QtWidgets>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include "objet.h"

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QMenuBar;
class QPushButton;
class QSpinBox;
class QTableWidget;
class QRadioButton;

QT_END_NAMESPACE


class MainWin : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWin();
    void createMenu();
    void createMainLayouts();
    void showResults();
    void createRadioButtons();
    void getMethod();
    QDialog* getMethodeDialog();


private:



    QMenuBar *menuBar;
    QDialog *methode_dialog;

    QPushButton *buttons[4];

    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *helpAction;
    QAction *aboutAction;
    QAction *exitAction;
    QString cheminFichier;

    QMainWindow *winRes;
    QMainWindow *winManuel;

    QSpinBox *nbObj;
    QSpinBox *capacite;

    QTableWidget *table;
    QPushButton *execute ;

    QList<Objet*> listeObj;

    int methode;
    QRadioButton *meth_heur_spec,*meth_prof,*meth_larg, *meth_prio;
    QGroupBox *choix_meth;

signals:

public slots:

    void sadFichier();
    void sadAleatoire();
    void sadManuel();
    void resizeTable();
    void executer();
    void retour();
    void aide();
    void lancerSAD();
    void sadExact();
    void sadGenetique();
    void sadSpecifique();
    void sadTabou();


};

#endif // MAINWIN_H
