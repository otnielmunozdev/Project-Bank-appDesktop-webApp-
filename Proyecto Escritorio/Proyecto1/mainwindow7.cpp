#include "mainwindow7.h"
#include "ui_mainwindow7.h"

MainWindow7::MainWindow7(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow7)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

MainWindow7::~MainWindow7()
{
    delete ui;
}

void MainWindow7::on_Salir12pushButton_clicked()
{
    this->setVisible(false);
}
