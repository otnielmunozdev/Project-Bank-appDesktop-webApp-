#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <dialog1.h>
#include "dialog1.h"
#include "mainwindow2.h"
#include "mainwindow6.h"
#include <QtSql>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);
     setWindowFlags(Qt::FramelessWindowHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoginpushButton_clicked()
{
    //Conector conn;
    QString Puesto,Codigo,Local,Nombre,User=ui->UsuariolineEdit->text();
    QString Password=ui->PasswordlineEdit->text(),msg;
    //QString x="admin", y="admin",a="ejecutivo",b="ejecutivo";

    conn.connOpen();
    //.database("BDDesk")
    QSqlQuery qry(conn.mydb);

    qry.prepare("SELECT * from empleado WHERE  id_empleado = '"+User+"' AND curp ='"+Password+"'");
    qry.exec();
    qry.first();
    //qry.next();

    Puesto=qry.value(3).toString();
    Local=qry.value(11).toString();
    Nombre=qry.value(1).toString();
    Codigo=qry.value(0).toString();
    //QMessageBox::information(this,tr("K"),Puesto);
    if(Puesto=="Administrador" or Puesto=="administrador" or Puesto=="adm")
    {
        ventana6 = new MainWindow2();
        ventana6->PuestoUsuario=Puesto;   // Puesto
        ventana6->NombreUsuario=Nombre;   // Nombre
        ventana6->CodigoUsuario=Codigo;
        ventana6->SetInfo();
        ventana6->setVisible(true);
        //this->setVisible(false);
        this->close();
    }
    else if(Puesto=="Empleado" or Puesto=="empleado" or Puesto=="emp")
    {
        MainWindow2 *ventana6 = new MainWindow2();
        ventana6->LocalActual=Local;  //Id Sucursal
        ventana6->PuestoUsuario=Puesto;
        ventana6->NombreUsuario=Nombre;     // Nombre
        ventana6->SetInfo();
        ventana6->setVisible(true);
        //this->setVisible(false);
        this->close();
    }
    else
    {
        QMessageBox::information(this,tr("Error"),tr("Usuario Incorrecto\n"));
    }
    //ui->UsuariolineEdit->setText(qry.value(2).toString());
   // else
        // QMessageBox::critical(this, "Datos Incorrectos","Datos Incorrectos");
    //if(qry.exec("select *from empleado where id_empleado'"+Password+"'"))
    // {
        //while(qry.next())
        //{
             //MainWindow2 *ventana6 = new MainWindow2();
            // ventana6->setVisible(true);
          //   this->setVisible(false);
        //}

       // conn.connClose();


     //} // while (query.next())
      // {
          // QString user = query.value(0).toString();
          // QString pass = query.value(1).toString();
          // if (user == username && pass == password)
              // ret = true;
      // }
}
