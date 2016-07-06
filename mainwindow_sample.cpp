#include "mainwindow_sample.h"
#include "ui_mainwindow_sample.h"

MainWindow_sample::MainWindow_sample(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_sample)
{
    ui->setupUi(this);
}

MainWindow_sample::~MainWindow_sample()
{
    delete ui;
}
