#ifndef MAINWINDOW_SAMPLE_H
#define MAINWINDOW_SAMPLE_H

#include <QMainWindow>

namespace Ui {
class MainWindow_sample;
}

class MainWindow_sample : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_sample(QWidget *parent = 0);
    ~MainWindow_sample();

private:
    Ui::MainWindow_sample *ui;
};

#endif // MAINWINDOW_SAMPLE_H
