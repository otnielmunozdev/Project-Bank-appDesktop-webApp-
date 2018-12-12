#include "mainwindow8.h"
#include "ui_mainwindow8.h"
#include "mainwindow6.h"
#include "mainwindow.h"
#include "QMessageBox"
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <conector.h>

MainWindow8::MainWindow8(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow8)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

MainWindow8::~MainWindow8()
{
    delete ui;

}

void MainWindow8::on_Salir5pushButton_clicked()
{
    Conta=0;
    this->close();
}

void MainWindow8::on_pushButton_clicked()
{
    Conector conn;
    QString IdCuenta,Nota,Dia,Costo;
    IdCuenta=ui->lineEdit->text();
    Nota=ui->lineEdit_3->text();
    Dia=ui->FechaEdit->text();
    Costo=ui->lineEdit_2->text();
    conn.connOpenWeb();
    QSqlQuery qry(conn.mydb);
    //qry.prepare("INSERT INTO cuenta (ID_Cuenta, tipo, id_cliente) values ('"+num_cuenta+
    qry.prepare("INSERT INTO movimiento (costo,referencia,fecha_de_compra, ID_Cuenta) values ('"+Costo+"', '"+Nota+"','"+Dia+"','"+IdCuenta+"')");
    if(qry.exec())
    {
        QMessageBox::information(this,tr(" "),tr("     Se le realizó el movimiento a la cuenta     "));
        conn.connClose();
    }
    else
    {
         QMessageBox::critical(this, "Error","No se realizó el movimiento");
    }
}
