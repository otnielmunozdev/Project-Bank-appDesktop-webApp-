#include "mainwindow5.h"
#include "ui_mainwindow5.h"
#include "mainwindow2.h"
#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlError>
#include <QtSqlVersion>

MainWindow5::MainWindow5(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow5)
{

    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    QSqlDatabase mDatabase = QSqlDatabase::addDatabase("QMYSQL");
    mDatabase.setHostName("localhost");
    mDatabase.setDatabaseName("Banco");
    mDatabase.setPort(3306);
    mDatabase.setPassword("lmao2420");
    mDatabase.setUserName("root");
    if(!mDatabase.open())
    {
        QMessageBox::critical(this, "Error", mDatabase.lastError().text());
        return;
    } 
    mModel = new QSqlTableModel(this);
    mModel->setTable("sucursal");
    mModel->select();
    ui->tableView->setModel(mModel);
}

MainWindow5::~MainWindow5()
{
    delete ui;
}

void MainWindow5::on_Salir5pushButton_clicked()
{
    //MainWindow2 *ventana7 = new MainWindow2();
    this->setVisible(false);
    //this->setVisible(false);
}
