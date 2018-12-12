#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include "mainwindow.h"
#include "mainwindow3.h"
#include "mainwindow4.h"
#include "mainwindow5.h"
#include <QMessageBox>
#include <thread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QThread>

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
    ventana2 = new MainWindow3();
    ventana3 = new MainWindow4();
    ventana0 = new MainWindow8();
    //setWindowFlags(Qt::FramelessWindowHint);
    //QMainWindow::showFullScreen();
}

MainWindow2::~MainWindow2()
{
    delete ui;
}
void MainWindow2::SetInfo()
{
    ui->Nombre->setText(NombreUsuario);
    ui->Puesto->setText(PuestoUsuario);
    //Mover();
}

void MainWindow2::on_HomepushButton_clicked()
{
    MainWindow *ventana1 = new MainWindow();
    ventana1->setVisible(true);
    this->close();
    if(ventana2->Conta!=0)
    {
        ventana2->close();
    }
    if(ventana3->Conta!=0)
    {
        ventana3->close();
    }
    if(ventana0->Conta!=0)
    {
        ventana0->close();
    }

}

void MainWindow2::on_EmpleadospushButton_clicked()
{
    if(ventana2==nullptr)
    {
        ventana2 = new MainWindow3;
    }
    if(PuestoUsuario=="Administrador" or PuestoUsuario=="administrador" or PuestoUsuario=="adm")
    {
        if(ventana2->Conta==0)
        {
            ventana2->CodigoUsuario=CodigoUsuario;
            ventana2->show();
            ventana2->Conta++;
        }
        else
        {
            QMessageBox::information(this,tr("Empleados"),tr("La ventana de Empleados ya se encuentra abierta.\n"));
        }
    //this->setVisible(false);
    }
    else
    {
        QMessageBox::information(this,tr("Error"),tr("Usuario no permitido, sección exclusiva para administradores\n"));
    }
}

void MainWindow2::on_SalirpushButton_clicked()
{

    if(ventana2->Conta!=0)
    {
        ventana2->close();
    }
    if(ventana3->Conta!=0)
    {
        ventana3->close();
    }
    if(ventana0->Conta!=0)
    {
        ventana0->close();
    }
    this->close();
}

void MainWindow2::on_ClientespushButton_clicked()
{
    Mover();
    if(ventana3==nullptr)
    {
        ventana3 = new MainWindow4();
    }
    if(PuestoUsuario=="Empleado" or PuestoUsuario=="empleado" or PuestoUsuario=="emp")
    {
        ventana3->LocalActual=LocalActual;
        ventana3->lock();
    }
    //En caso de ser adm la variable de Local Actual (id Sucursal)
    //Se queda vacia, ya que  el adm puede agregar sin limitante
    //Caso contrario se activa el if de arriba y se pasa la variable del id de la sucursal
    ventana3->PuestoUsuario=PuestoUsuario;
    ventana3->NombreUsuario=NombreUsuario;
    ventana3->CodigoUsuario=CodigoUsuario;

    if(ventana3->Conta==0)
    {
        ventana3->show();
        ventana3->Conta++;
    }
    else
    {
        QMessageBox::information(this,tr("Clientes"),tr("La ventana de Clientes ya se encuentra abierta.\n"));
    }
    //this->setVisible(false);
}

void MainWindow2::on_actionMostrar_triggered()
{
    MainWindow5 *ventana8 = new MainWindow5();
    ventana8->show();
    //ventana8->setVisible(true);
    //this->setVisible(false);
}

void MainWindow2::on_actionMostrar_2_triggered()
{
    QMessageBox::information(this,tr("Ayuda"),tr("Este es el menú del administrador\n"
                                                 "*Selecciona Empleados:  Para dar de alta/modificar/eliminar empleados\n"
                                                 "*Selecciona Clientes:   Para dar de alta/modificar/desactivar clientes y cuentas y/o sus servicios\n"
                                                 "*Selecciona Sucursales: Para visualizar las sucursales\n"
                                                 "*Selecciona Regresar:   Para salir de la sesion\n"
                                                 "*Selecciona Salir:      Para salir del sistema"));
}
int MainWindow2::Cantidad(QString DB, int b)
{
    Conector conn;
    if(b==0)
    {
        conn.connOpen();
        QSqlQuery qry(conn.mydb);

        qry.prepare("select count(1) from "+DB+"");
        if(qry.exec())
        {
            qry.first();
            return qry.value(0).toInt();
            //ui->progressBar->setValue(Cant);//Acá se hace el conteo inicial
        }
        else
        {
            return -1;
        }
    }
    else if(b==1)
    {
        conn.connOpenWeb();
        QSqlQuery qry2(conn.mydb);
        qry2.prepare("select count(1) from "+DB+"");
        if(qry2.exec())
        {
            qry2.first();
            return qry2.value(0).toInt();
        }
        else
        {
            return -1;
        }
    }
    conn.connClose();
    return -1;
}

void MainWindow2::Mover()
{
    int Cant=0,Cant2=0;
    bool Bandera=true;
    Cant=Cantidad("cliente",0);
    Cant2=Cantidad("cliente",1);
    if(Cant!=Cant2)
    {
        Bandera=false;
        //ui->label_3->setStyleSheet("border-image: url(:/imagenes/rojo.png);");
        QMessageBox::critical(this, "Error","Ocurrió un problema con la información de los clientes");
    }
    else
    {
        //ui->label_3->setStyleSheet("border-image: url(:/imagenes/verde.png);");
        //ui->label_3->show();

    }
    Cant=Cantidad("citas",0);
    Cant2=Cantidad("cita",1);
    if(Cant!=Cant2)
    {
        Bandera=false;
        //ui->label_3->setStyleSheet("border-image: url(:/imagenes/rojo.png);");
        QMessageBox::critical(this, "Error","Ocurrió un problema con la información de las citas");
    }
    else
    {
        //ui->label_3->setStyleSheet("border-image: url(:/imagenes/verde.png);");
    }
    Cant=Cantidad("credito_hipotecario",0);
    Cant2=Cantidad("credito_hipotecario",1);
    if(Cant!=Cant2)
    {
        Bandera=false;
        //ui->label_3->setStyleSheet("border-image: url(:/imagenes/rojo.png);");
        QMessageBox::critical(this, "Error","Ocurrió un problema con la información de los creditos hipotecarios");
    }
    else
    {
        //ui->label_3->setStyleSheet("border-image: url(:/imagenes/verde.png);");
    }
    Cant=Cantidad("cuenta",0);
    Cant2=Cantidad("cuenta",1);
    if(Cant!=Cant2)
    {
        Bandera=false;
        //ui->label_3->setStyleSheet("border-image: url(:/imagenes/rojo.png);");
        QMessageBox::critical(this, "Error","Ocurrió un problema con la información de las cuentas");
    }
    else
    {
        //ui->label_3->setStyleSheet("border-image: url(:/imagenes/verde.png);");
    }
    if(Bandera)
    {
        ui->label_3->setStyleSheet("border-image: url(:/imagenes/verde.png);");
    }
    else
    {
        ui->label_3->setStyleSheet("border-image: url(:/imagenes/rojo.png);");
    }
}

void MainWindow2::on_pushButton_clicked()
{
   Mover();
}

void MainWindow2::on_pushButton_2_clicked()
{
    Corre=false;
}

void MainWindow2::on_pushButton_3_clicked()
{
    if(ventana0==nullptr)
    {
        ventana0 = new MainWindow8();
    }

    if(ventana0->Conta==0)
    {
        ventana0->show();
        ventana0->Conta++;
    }
    else
    {
        QMessageBox::information(this,tr("Clientes"),tr("La ventana de Pagos/Compra ya se encuentra abierta.\n"));
    }
}
