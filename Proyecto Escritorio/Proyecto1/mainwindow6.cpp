#include "mainwindow6.h"
#include "ui_mainwindow6.h"
#include "mainwindow.h"
#include "mainwindow7.h"
#include "mainwindow8.h"

MainWindow6::MainWindow6(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow6)
{
    ui->setupUi(this);
}

MainWindow6::~MainWindow6()
{
    delete ui;
}

void MainWindow6::on_Home2pushButton_clicked()
{
    MainWindow *ventana9 = new MainWindow();
    ventana9->setVisible(true);
    this->setVisible(false);
}

void MainWindow6::on_EmpleadoSalirpushButton_clicked()
{

}

void MainWindow6::on_ClientesEmpleadospushButton_clicked()
{
    MainWindow7 *ventana10 = new MainWindow7();
    ventana10->show();
}

void MainWindow6::on_actionMostrar_triggered()
{
    MainWindow8 *ventana11 = new MainWindow8();
    ventana11->show();
}

void MainWindow6::on_pushButton_clicked()
{
    ui->lcdNumber->display(LocalActual);
}
