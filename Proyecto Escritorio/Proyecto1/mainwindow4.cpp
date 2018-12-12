#include "mainwindow4.h"
#include "ui_mainwindow4.h"
#include "mainwindow2.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QDate>
#include "conector.h"


MainWindow4::MainWindow4(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow4)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->IdClientelineEdit->setEnabled(false);

    mailREX.setPattern("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    NumberREX.setPattern("\\w{8,10}");
    NumberREX.setCaseSensitivity(Qt::CaseInsensitive);
    NumberREX.setPatternSyntax(QRegExp::RegExp);

    //En caso de que olvidara algo, el botón de cada id se tiene que activar en cada sección que el cuadro de ID debería.
    //Solo sería agregar en enable en las partes que me haya faltado.
}

MainWindow4::~MainWindow4()
{
    delete ui;
}
void MainWindow4::lock()
{
    ui->ID_sucClientelineEdit->setText(LocalActual);
    ui->ID_sucClientelineEdit->setEnabled(false);
}

void MainWindow4::on_Salir12pushButton_clicked()
{
   // MainWindow2 *ventana6 = new MainWindow2();
    //ventana6->setVisible(true);
    //this->setVisible(false);
    this->setVisible(false);
    Conta=0;
}

void MainWindow4::on_AgregarClientepushButton_clicked()
{
    //int x=1;
    QString id_cliente, sexo, ciudad, fecha_nac, telefono, curp, domicilio, correo_electronico, nombre, id_suc;
    id_cliente=ui->IdClientelineEdit->text();
    sexo = ui->SexocomboBox->currentText();
    ciudad = ui->CiudadlineEdit->text();
    fecha_nac = ui->FechaNacClientedateEdit->text();
    telefono = ui->TelefonoClientelineEdit->text();
    curp = ui->CURPclientelineEdit->text();
    domicilio=ui->DomiciliolineEdit->text();
    correo_electronico = ui->CorreoClientelineEdit->text();
    nombre = ui->NombreClientelineEdit->text();
    id_suc = ui->ID_sucClientelineEdit->text();
    bool Esc=false,Web=false;
    conn.connOpen();
               // inicio de la transacción
    //conn.connOpen();                  // Se abre la base de datos Desk
    QSqlQuery qry(conn.mydb);
    qry.prepare("INSERT INTO cliente (id_cliente, sexo, ciudad, fecha_nac, telefono, curp, domicilio, correo_electronico ,nombre, id_suc,activo) values ('"+id_cliente+"','"+sexo+"', '"+ciudad+"','"+fecha_nac+"','"+telefono+"', '"+curp+"', '"+domicilio+"', '"+correo_electronico+"', '"+nombre+"', '"+id_suc+"','0')");
    if(qry.exec())
    {
        Esc=true;
    }
    conn.connOpenWeb();
    QSqlQuery qry2(conn.mydb);
    qry2.prepare("INSERT INTO cliente (id_cliente, nombre, email ,telefono, contrasenia) values ('"+id_cliente+"','"+nombre+"','"+correo_electronico+"','"+telefono+"','0000')");
    if(qry2.exec())
    {
        Web=true;
    }
    if(Esc && Web)
    {
        QMessageBox::information(this,tr("Guardando"),tr("     Los datos se agregaron a la Base de Datos     "));
        ui->IdClientelineEdit->clear();
        ui->NombreClientelineEdit->clear();
        ui->CURPclientelineEdit->clear();
        ui->CiudadlineEdit->clear();
        ui->CorreoClientelineEdit->clear();
        ui->TelefonoClientelineEdit->clear();
        if(PuestoUsuario!="Empleado" && PuestoUsuario!="empleado" && PuestoUsuario!="emp")
        {
            ui->ID_sucClientelineEdit->clear();
        }
        ui->DomiciliolineEdit->clear();
        //conn.connClose();
        conn.mydb.close();
    }
    else
    {
       QMessageBox::critical(this, "Error","Llena el formulario correctamente");
    }
    if(Web==false)
    {
        QMessageBox::critical(this, "Error","Error conexión Web");
    }
    if(Esc==false)
    {
        QMessageBox::critical(this, "Error","Error conexión Escritorio");
    }
}

void MainWindow4::on_ModificarClientepushButton_clicked()
{
    QString id_cliente, sexo, ciudad, fecha_nac, telefono, curp, domicilio, correo_electronico, nombre, id_suc;
    id_cliente=ui->IdClientelineEdit_2->text();
    sexo = ui->ModificarSexocomboBox->currentText();
    ciudad = ui->ModificarCiudadlineEdit->text();
    fecha_nac = ui->ModificarFechaNacClientedateEdit->text();
    telefono = ui->ModificarTelefonoClientelineEdit->text();
    curp = ui->ModificarCURPclientelineEdit->text();
    domicilio=ui->ModificarDomiciliolineEdit->text();
    correo_electronico = ui->ModificarCorreoClientelineEdit->text();
    nombre = ui->ModificarNombreClientelineEdit->text();
    id_suc = ui->ModificarID_suclineEdit->text();
    bool Esc=false,Web=false;

    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("update cliente set sexo = '"+sexo+"', ciudad = '"+ciudad+"' , fecha_nac = '"+fecha_nac+"', telefono = '"+telefono+"', curp = '"+curp+"',domicilio =  '"+domicilio+"',correo_electronico = '"+correo_electronico+"',nombre = '"+nombre+"',id_suc =  '"+id_suc+"' where id_cliente = '"+id_cliente+"'");
    if(qry.exec())
    {
        Esc=true;
    }
    conn.connOpenWeb();
    QSqlQuery qry2(conn.mydb);
    qry2.prepare("update cliente set telefono = '"+telefono+"', nombre = '"+nombre+"' , email = '"+correo_electronico+"' where id_cliente = '"+id_cliente+"'");
    if(qry2.exec())
    {
        Web=true;
    }
    if(Esc && Web)
    {
        QMessageBox::information(this,tr("Modificacion"),tr("          El Cliente se ha modificado correctamente     "));
        ui->IdClientelineEdit_2->clear();
        ui->ModificarSexocomboBox->clearEditText();
        ui->ModificarCiudadlineEdit->clear();
        ui->ModificarFechaNacClientedateEdit->clear();
        ui->ModificarTelefonoClientelineEdit->clear();
        ui->ModificarCURPclientelineEdit->clear();
        ui->ModificarDomiciliolineEdit->clear();
        ui->ModificarCorreoClientelineEdit->clear();
        ui->ModificarNombreClientelineEdit->clear();
        ui->ModificarID_suclineEdit->clear();
        ui->BuscarClientelineEdit_2->clear();

        ui->IdClientelineEdit_2->setEnabled(false);
        ui->ModificarSexocomboBox->setEnabled(false);
        ui->ModificarCiudadlineEdit->setEnabled(false);
        ui->ModificarFechaNacClientedateEdit->setEnabled(false);
        ui->ModificarTelefonoClientelineEdit->setEnabled(false);
        ui->ModificarCURPclientelineEdit->setEnabled(false);
        ui->ModificarDomiciliolineEdit->setEnabled(false);
        ui->ModificarCorreoClientelineEdit->setEnabled(false);
        ui->ModificarNombreClientelineEdit->setEnabled(false);
        ui->ModificarID_suclineEdit->setEnabled(false);
        ui->EliminarClientepushButton->setEnabled(false);
        ui->ModificarClientepushButton->setEnabled(false);
        ui->CancelarClientesBpushButton->setEnabled(false);
        ui->EliminarClientepushButton->setEnabled(false);
        ui->ActivarClientepushButton->setEnabled(false);
        conn.connClose();
     }
     else
        QMessageBox::critical(this, "Error","Llena el formulario correctamente, los datos son:\n*Datos incompletos\n*Datos Erroneos");
         //QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    if(Web==false)
    {
        QMessageBox::critical(this, "Error","Error conexión Web");
    }
    if(Esc==false)
    {
        QMessageBox::critical(this, "Error","Error conexión Escritorio");
    }
}

void MainWindow4::on_BuscarClientePushButton_2_clicked()
{
    QString buscar=ui->BuscarClientelineEdit_2->text();
    QDate date = QDate::currentDate();
    QString dateString = date.toString();
    conn.connOpen();
    QSqlQuery  qry(conn.mydb);
    if(PuestoUsuario=="Empleado" or PuestoUsuario=="empleado" or PuestoUsuario=="emp")
    {
        qry.prepare("SELECT * from cliente WHERE  id_cliente = '"+buscar+"' AND id_suc = '"+LocalActual+"'");
        //Con esto limitas a que el cliente SOLO pueda buscar clientes que sean de la misma sucursal donde él trabaja
    }
    else
    {
        qry.prepare("SELECT * from cliente WHERE  id_cliente = '"+buscar+"'");
        //El administrador no sufre de ese efecto.
    }
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->IdClientelineEdit_2->setText(qry.value(0).toString());
            ui->ModificarSexocomboBox->setCurrentText(qry.value(1).toString());
            ui->ModificarCiudadlineEdit->setText(qry.value(2).toString());
            ui->ModificarFechaNacClientedateEdit->setDate(qry.value(3).toDate());
            ui->ModificarTelefonoClientelineEdit->setText(qry.value(4).toString());
            ui->ModificarCURPclientelineEdit->setText(qry.value(5).toString());
            ui->ModificarDomiciliolineEdit->setText(qry.value(6).toString());
            ui->ModificarCorreoClientelineEdit->setText(qry.value(7).toString());
            ui->ModificarNombreClientelineEdit->setText(qry.value(8).toString());
            ui->ModificarID_suclineEdit->setText(qry.value(9).toString());


            ui->ModificarSexocomboBox->setEnabled(true);
            ui->ModificarCiudadlineEdit->setEnabled(true);
            ui->ModificarFechaNacClientedateEdit->setEnabled(true);
            ui->ModificarTelefonoClientelineEdit->setEnabled(true);
            ui->ModificarCURPclientelineEdit->setEnabled(true);
            ui->ModificarDomiciliolineEdit->setEnabled(true);
            ui->ModificarCorreoClientelineEdit->setEnabled(true);
            ui->ModificarNombreClientelineEdit->setEnabled(true);
            if(PuestoUsuario=="Administrador" or PuestoUsuario=="administrador" or PuestoUsuario=="adm")
            {
                //Solo el administrador debería poder mover a los clientes de sucursal.
                ui->ModificarID_suclineEdit->setEnabled(true);
            }

            ui->ModificarClientepushButton->setEnabled(true);
            ui->EliminarClientepushButton->setEnabled(true);
            ui->CancelarClientesBpushButton->setEnabled(true);
            ui->EliminarClientepushButton->setEnabled(true);
            ui->ActivarClientepushButton->setEnabled(true);
            QMessageBox::information(this,tr(" "),tr("Los campos se han activado se pueden\n *Modificar\n*Eliminar\n*Dar de alta\n*Dar de Baja     "));
        }
        conn.connClose();
     }
     else
    {
       // QMessageBox::critical(this, "Error","Llena el formulario correctamente");
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}

void MainWindow4::on_CancelarClientesBpushButton_clicked()
{
    ui->IdClientelineEdit_2->clear();
    ui->ModificarSexocomboBox->clearEditText();
    ui->ModificarCiudadlineEdit->clear();
    ui->ModificarFechaNacClientedateEdit->clear();
    ui->ModificarTelefonoClientelineEdit->clear();
    ui->ModificarCURPclientelineEdit->clear();
    ui->ModificarDomiciliolineEdit->clear();
    ui->ModificarCorreoClientelineEdit->clear();
    ui->ModificarNombreClientelineEdit->clear();
    ui->ModificarID_suclineEdit->clear();
    ui->BuscarClientelineEdit_2->clear();

    ui->IdClientelineEdit_2->setEnabled(false);
    ui->ModificarSexocomboBox->setEnabled(false);
    ui->ModificarCiudadlineEdit->setEnabled(false);
    ui->ModificarFechaNacClientedateEdit->setEnabled(false);
    ui->ModificarTelefonoClientelineEdit->setEnabled(false);
    ui->ModificarCURPclientelineEdit->setEnabled(false);
    ui->ModificarDomiciliolineEdit->setEnabled(false);
    ui->ModificarCorreoClientelineEdit->setEnabled(false);
    ui->ModificarNombreClientelineEdit->setEnabled(false);
    ui->ModificarID_suclineEdit->setEnabled(false);
    ui->EliminarClientepushButton->setEnabled(false);
    ui->ModificarClientepushButton->setEnabled(false);
    ui->CancelarClientesBpushButton->setEnabled(false);
    ui->EliminarClientepushButton->setEnabled(false);
    ui->ActivarClientepushButton->setEnabled(false);
}

void MainWindow4::on_EliminarClientepushButton_clicked()
{
    QString id_cliente,num_cuenta="";
    id_cliente=ui->IdClientelineEdit_2->text();
    conn.connOpen();
    QSqlQuery qry(conn.mydb),qry2(conn.mydb),qry3(conn.mydb),qryCancel(conn.mydb);
    qry.prepare("update cliente set activo = '0' where id_cliente = '"+id_cliente+"'");
    qry3.prepare("select num_cuenta from cuenta where id_cliente ='"+id_cliente+"'");  //Recuperas la lista de numeros de cuenta de ese cliente
    qry3.exec();
    qry2.prepare("update cuenta set activo = '0' where id_cliente = '"+id_cliente+"'");
    if(qry.exec() && qry2.exec())
    {

        QMessageBox::information(this,tr("Baja"),tr("El Cliente a sido dado de baja en el sistema,al igual que sus cuentas"));
        ui->IdClientelineEdit_2->clear();
        ui->ModificarSexocomboBox->clearEditText();
        ui->ModificarCiudadlineEdit->clear();
        ui->ModificarFechaNacClientedateEdit->clear();
        ui->ModificarTelefonoClientelineEdit->clear();
        ui->ModificarCURPclientelineEdit->clear();
        ui->ModificarDomiciliolineEdit->clear();
        ui->ModificarCorreoClientelineEdit->clear();
        ui->ModificarNombreClientelineEdit->clear();
        ui->ModificarID_suclineEdit->clear();
        ui->BuscarClientelineEdit_2->clear();

        ui->IdClientelineEdit_2->setEnabled(false);
        ui->ModificarSexocomboBox->setEnabled(false);
        ui->ModificarCiudadlineEdit->setEnabled(false);
        ui->ModificarFechaNacClientedateEdit->setEnabled(false);
        ui->ModificarTelefonoClientelineEdit->setEnabled(false);
        ui->ModificarCURPclientelineEdit->setEnabled(false);
        ui->ModificarDomiciliolineEdit->setEnabled(false);
        ui->ModificarCorreoClientelineEdit->setEnabled(false);
        ui->ModificarNombreClientelineEdit->setEnabled(false);
        ui->ModificarID_suclineEdit->setEnabled(false);
        ui->EliminarClientepushButton->setEnabled(false);
        ui->ModificarClientepushButton->setEnabled(false);
        ui->CancelarClientesBpushButton->setEnabled(false);
        ui->EliminarClientepushButton->setEnabled(false);
        ui->ActivarClientepushButton->setEnabled(false);
        qry3.first();  //Todos los qry por defecto comienzan en null, acá pones el qry sobre la primer posición
        if(qry3.isValid())
        {
            do
            {
                num_cuenta=qry3.value(0).toString();  //Pasamos el valor de la cuenta a un string
                QMessageBox::information(this,tr("Cuenta a desactivar"),num_cuenta);
                qryCancel.prepare("update seguros set activo = '0' where num_cuenta = '"+num_cuenta+"'");
                qryCancel.exec();
                qryCancel.prepare("update prestamo set activo = '0' where num_cuenta = '"+num_cuenta+"'");
                qryCancel.exec();
                qryCancel.prepare("update credito_hipotecario set activo = '0' where num_cuenta = '"+num_cuenta+"'");
                qryCancel.exec();
                qryCancel.prepare("update inversion set activo = '0' where num_cuenta = '"+num_cuenta+"'");
                qryCancel.exec();
                qry3.next();
            }
            while(qry3.isValid());  //nextResult nos mueve a la posición siguiente de la lista
        }
        conn.connClose();
     }
     else
       // QMessageBox::critical(this, "Error","No se pudo dar de Baja");
     QMessageBox::critical(this,tr("error::"),qry.lastError().text());

}

void MainWindow4::on_ActivarClientepushButton_clicked()
{
    QString id_cliente;
    id_cliente=ui->IdClientelineEdit_2->text();
    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("update cliente set activo = '1' where id_cliente = '"+id_cliente+"'");
    if(qry.exec())
    {
        QMessageBox::information(this,tr("Alta"),tr("          El Cliente a sido dado de alta en el sistema     "));
        ui->IdClientelineEdit_2->clear();
        ui->ModificarSexocomboBox->clearEditText();
        ui->ModificarCiudadlineEdit->clear();
        ui->ModificarFechaNacClientedateEdit->clear();
        ui->ModificarTelefonoClientelineEdit->clear();
        ui->ModificarCURPclientelineEdit->clear();
        ui->ModificarDomiciliolineEdit->clear();
        ui->ModificarCorreoClientelineEdit->clear();
        ui->ModificarNombreClientelineEdit->clear();
        ui->ModificarID_suclineEdit->clear();
        ui->BuscarClientelineEdit_2->clear();

        ui->IdClientelineEdit_2->setEnabled(false);
        ui->ModificarSexocomboBox->setEnabled(false);
        ui->ModificarCiudadlineEdit->setEnabled(false);
        ui->ModificarFechaNacClientedateEdit->setEnabled(false);
        ui->ModificarTelefonoClientelineEdit->setEnabled(false);
        ui->ModificarCURPclientelineEdit->setEnabled(false);
        ui->ModificarDomiciliolineEdit->setEnabled(false);
        ui->ModificarCorreoClientelineEdit->setEnabled(false);
        ui->ModificarNombreClientelineEdit->setEnabled(false);
        ui->ModificarID_suclineEdit->setEnabled(false);
        ui->EliminarClientepushButton->setEnabled(false);
        ui->ModificarClientepushButton->setEnabled(false);
        ui->CancelarClientesBpushButton->setEnabled(false);
        ui->EliminarClientepushButton->setEnabled(false);
        ui->ActivarClientepushButton->setEnabled(false);
        conn.connClose();
     }
     else
     //   QMessageBox::critical(this, "Error","No se pudo dar de Alta");
     QMessageBox::critical(this,tr("error::"),qry.lastError().text());

}

void MainWindow4::on_GenerarNumCuentapushButton_clicked()
{
    MainWindow x;
    /*
    QString i,j;
    qsrand(time(NULL)); //el contador va aumentando deacuerdo al tiempo en el que tarda en presionar el boton
    for(int y=0; y<5; y++)
    {
    int random1 = qrand()%1000;//declaro un entero el random de 0-1000

    i.setNum(random1);//hago que el QString o cadena pase al random
    j.append(i);//inserto la cadena uno en la cadena 2

    }
    */
    ui->NumCuentalineEdit->setText(x.RandmKeyN(16));
}

void MainWindow4::on_GenerarCodigoSeguridadpushButton_clicked()
{
    MainWindow x;
    /*
    QString i,j;
    qsrand(time(NULL)); //el contador va aumentando deacuerdo al tiempo en el que tarda en presionar el boton
    for(int y=0; y<2; y++)
    {
    int random1 = qrand()%1000;//declaro un entero el random de 0-1000

    i.setNum(random1);//hago que el QString o cadena pase al random
    j.append(i);//inserto la cadena uno en la cadena 2

    }
    */
    ui->CodigoSeguridadlineEdit->setText(x.RandmKeyN(4));
}

void MainWindow4::on_AgregarCuentapushButton_clicked()
{
    QString num_cuenta, saldo, tipo, codigo_seguridad, fecha_tramite, id_cliente;
    num_cuenta=ui->NumCuentalineEdit->text();
    saldo = ui->SaldolineEdit->text();
    tipo = ui->TipolineEdit->text();
    codigo_seguridad = ui->CodigoSeguridadlineEdit->text();
    fecha_tramite = ui->FechTramitedateEdit->text();
    id_cliente = ui->BuscarClientelineEdit->text();
    bool Esc=false, Web=false;

    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("INSERT INTO cuenta (num_cuenta, saldo, tipo, codigo_seguridad, fecha_tramite, id_cliente,activo,fecha_corte) values ('"+num_cuenta+"','"+saldo+"', '"+tipo+"','"+codigo_seguridad+"','"+fecha_tramite+"', '"+id_cliente+"','1','"+fecha_tramite+"')");

    if(qry.exec())
    {
        Esc=true;
    }
    conn.connOpenWeb();
    QSqlQuery qry2(conn.mydb);
    qry2.prepare("INSERT INTO cuenta (ID_Cuenta, tipo, id_cliente) values ('"+num_cuenta+"', '"+tipo+"','"+id_cliente+"')");
    if(qry2.exec())
    {
        Web=true;
    }
    if(Esc && Web)
    {
        QMessageBox::information(this,tr(" "),tr("     Se le agrego una nueva cuenta al cliente     "));
        ui->NumCuentalineEdit->clear();
        ui->SaldolineEdit->clear();
        ui->TipolineEdit->clear();
        ui->CodigoSeguridadlineEdit->clear();
        ui->BuscarClientelineEdit->clear();
        ui->CuentasTableview->clearSpans();



        ui->SaldolineEdit->setEnabled(false);
        ui->TipolineEdit->setEnabled(false);
        ui->FechTramitedateEdit->setEnabled(false);
        ui->GenerarCodigoSeguridadpushButton->setEnabled(false);
        ui->GenerarNumCuentapushButton->setEnabled(false);
        ui->AgregarCuentapushButton->setEnabled(false);
        ui->CancelarCuentapushButton->setEnabled(false);



        conn.connClose();
    }
    else
        QMessageBox::critical(this, "Error","Llena el formulario correctamente");
       //  QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    if(Web==false)
    {
        QMessageBox::critical(this, "Error","Error conexión Web");
    }
    if(Esc==false)
    {
        QMessageBox::critical(this, "Error","Error conexión Escritorio");
    }
}

void MainWindow4::on_BuscarClientePushButton_clicked()
{
    QString buscar=ui->BuscarClientelineEdit->text();
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery qry(conn.mydb),qry2(conn.mydb);
    bool x=false;

    //qry.prepare("SELECT cuenta.num_cuenta,cuenta.saldo,cuenta.tipo,cuenta.codigo_seguridad,cuenta.fecha_tramite,cuenta.id_cliente,cuenta.activo,cliente.activo  FROM cuenta  INNER JOIN cliente  ON cuenta.id_cliente='"+buscar+"'=cliente.id_cliente WHERE cliente.activo='1'");
    if(PuestoUsuario=="Empleado" or PuestoUsuario=="empleado" or PuestoUsuario=="emp")
    {
        qry.prepare("SELECT cliente.id_cliente,cliente.activo FROM cliente  WHERE cliente.activo='1' AND cliente.id_cliente='"+buscar+"' AND id_suc = '"+LocalActual+"' ");
        //Con esto limitas a que el cliente SOLO pueda buscar clientes que sean de la misma sucursal donde él trabaja
    }
    else
    {
        qry.prepare("SELECT cliente.id_cliente,cliente.activo FROM cliente  WHERE cliente.activo='1' AND cliente.id_cliente='"+buscar+"'");
        //El administrador no sufre de ese efecto.
    }
    qry.exec();
    while(qry.next())
      {
        x=true;
        if(x==true)
        {
            if(PuestoUsuario=="Empleado" or PuestoUsuario=="empleado" or PuestoUsuario=="emp")
            {
                qry2.prepare("SELECT cuenta.num_cuenta,cuenta.activo,cuenta.saldo,cuenta.tipo,cuenta.codigo_seguridad,cuenta.fecha_tramite,cuenta.id_cliente,cliente.activo, cliente.id_suc  FROM cuenta  INNER JOIN cliente  ON cuenta.id_cliente=cliente.id_cliente WHERE cliente.id_cliente='"+buscar+"' AND cliente.id_suc = '"+LocalActual+"' ");
            }
            else
            {
                qry2.prepare("SELECT cuenta.num_cuenta,cuenta.activo,cuenta.saldo,cuenta.tipo,cuenta.codigo_seguridad,cuenta.fecha_tramite,cuenta.id_cliente,cliente.activo  FROM cuenta  INNER JOIN cliente  ON cuenta.id_cliente=cliente.id_cliente WHERE cliente.id_cliente='"+buscar+"'");
            }
            qry2.exec();
            modal->setQuery(qry2);
            ui->CuentasTableview->setModel(modal);
            ui->SaldolineEdit->setEnabled(true);
            ui->TipolineEdit->setEnabled(true);
            ui->AgregarCuentapushButton->setEnabled(true);
            ui->FechTramitedateEdit->setEnabled(true);
            ui->CancelarCuentapushButton->setEnabled(true);
            ui->GenerarCodigoSeguridadpushButton->setEnabled(true);
            ui->GenerarNumCuentapushButton->setEnabled(true);
            QMessageBox::information(this,tr("Cargando"),tr("Se encontro el cliente en el sistema"));
        }
      }
      if(x==false){
          ui->SaldolineEdit->setEnabled(false);
          ui->TipolineEdit->setEnabled(false);
          ui->AgregarCuentapushButton->setEnabled(false);
          ui->FechTramitedateEdit->setEnabled(false);
          ui->CancelarCuentapushButton->setEnabled(false);
          ui->GenerarCodigoSeguridadpushButton->setEnabled(false);
          ui->GenerarNumCuentapushButton->setEnabled(false);
      QMessageBox::critical(this, "Error","*Verifica que el cliente exista y este activo");}

}

void MainWindow4::on_CuentasTableview_activated(const QModelIndex &index)
{
    QString val = ui->CuentasTableview->model()->data(index).toString();
    QString  num_cuenta, saldo, tipo, codigo_seguridad,fecha_tramite,id_cliente;
    num_cuenta=ui->NumCuentalineEdit->text();
    saldo = ui->SaldolineEdit->text();
    tipo = ui->TipolineEdit->text();
    codigo_seguridad = ui->CodigoSeguridadlineEdit->text();
    fecha_tramite = ui->FechTramitedateEdit->text();
    id_cliente = ui->BuscarClientelineEdit->text();

    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("select * from cuenta WHERE num_cuenta='"+val+"'");

    if(qry.exec())
   {
         QMessageBox::information(this,tr("Alta o Baja"),tr("*Tabla desactivada"));
        while(qry.next())
        {
            ui->NumCuentalineEdit->setText(qry.value(0).toString());
            ui->SaldolineEdit->setText(qry.value(1).toString());
            ui->TipolineEdit->setText(qry.value(2).toString());
            ui->CodigoSeguridadlineEdit->setText(qry.value(3).toString());
            ui->FechTramitedateEdit->setDate(qry.value(4).toDate());
            ui->TipolineEdit->setEnabled(false);
            ui->ActivarCuentapushButton->setEnabled(true);
            ui->DesactivarCuentapushButton->setEnabled(true);
            ui->GenerarCodigoSeguridadpushButton->setEnabled(false);
            ui->GenerarNumCuentapushButton->setEnabled(false);
            ui->SaldolineEdit->setEnabled(false);
            ui->FechTramitedateEdit->setEnabled(false);
            ui->AgregarCuentapushButton->setEnabled(false);


        }
       // conn.connClose();
     }
     else
    {
        QMessageBox::critical(this, "Error","No se cargaron los datos");
        // QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }

}

void MainWindow4::on_CancelarCuentapushButton_clicked()
{
    ui->NumCuentalineEdit->clear();
    ui->SaldolineEdit->clear();
    ui->TipolineEdit->clear();
    ui->CodigoSeguridadlineEdit->clear();
    ui->FechTramitedateEdit->clear();
    ui->ID_sucClientelineEdit->clear();
    ui->BuscarClientelineEdit->clear();
    ui->GenerarCodigoSeguridadpushButton->setEnabled(false);
    ui->GenerarNumCuentapushButton->setEnabled(false);
    ui->AgregarCuentapushButton->setEnabled(false);
    ui->DesactivarCuentapushButton->setEnabled(false);
    ui->CancelarCuentapushButton->setEnabled(false);
    ui->ActivarCuentapushButton->setEnabled(false);
    ui->FechTramitedateEdit->setEnabled(false);
    ui->TipolineEdit->setEnabled(false);
    ui->SaldolineEdit->setEnabled(false);
    conn.connClose();

}

void MainWindow4::on_BuscarCitaClientePushButton_clicked()
{
    QString buscar=ui->BuscarCitalineEdit->text();
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    bool x=false;
    if(PuestoUsuario=="Empleado" or PuestoUsuario=="empleado" or PuestoUsuario=="emp")
    {
        qry.prepare("SELECT citas.id_cita,citas.fecha,citas.hora,citas.sucursal,citas.id_cliente,cliente.nombre,cliente.activo,cliente.id_suc FROM citas  INNER JOIN cliente  ON citas.id_cliente=cliente.id_cliente WHERE citas.id_cita='"+buscar+"' AND cliente.id_suc = '"+LocalActual+"'");
    }
    else
    {
        qry.prepare("SELECT citas.id_cita,citas.fecha,citas.hora,citas.sucursal,citas.id_cliente,cliente.nombre,cliente.activo FROM citas  INNER JOIN cliente  ON citas.id_cliente=cliente.id_cliente WHERE citas.id_cita='"+buscar+"'");
    }
    qry.exec();
    while( qry.next())
      {
        x=true;
        if(x==true){
        modal->setQuery(qry);
        ui->tableView->setModel(modal);
        QMessageBox::information(this,tr(" "),tr("Se encontro la cita en el sistema"));}
      }
      if(x==false){

      QMessageBox::critical(this, "Error","*Verifica que ingresaste bien el ID cita\n*La cita no esta registrada");}


}

void MainWindow4::on_ActivarCuentapushButton_clicked()
{
    QString num_cuenta;
    num_cuenta=ui->NumCuentalineEdit->text();
    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("update cuenta set activo = '1' where num_cuenta = '"+num_cuenta+"'");
    if(qry.exec())
    {
        QMessageBox::information(this,tr("Activada"),tr("La cuenta del cliente a sido activada "));
        on_BuscarClientePushButton_clicked();
        ui->NumCuentalineEdit->clear();
        ui->SaldolineEdit->clear();
        ui->TipolineEdit->clear();
        ui->CodigoSeguridadlineEdit->clear();
        ui->FechTramitedateEdit->clear();
        ui->SaldolineEdit->setEnabled(true);
        ui->TipolineEdit->setEnabled(true);
        ui->AgregarCuentapushButton->setEnabled(true);
        ui->FechTramitedateEdit->setEnabled(true);
        ui->CancelarCuentapushButton->setEnabled(true);
        ui->GenerarCodigoSeguridadpushButton->setEnabled(true);
        ui->GenerarNumCuentapushButton->setEnabled(true);
        ui->DesactivarCuentapushButton->setEnabled(false);
        ui->ActivarCuentapushButton->setEnabled(false);

      //  conn.connClose();
     }
     else
        QMessageBox::critical(this, "Error","No se pudo dar de alta");
}

void MainWindow4::on_DesactivarCuentapushButton_clicked()
{
    QString num_cuenta;
    num_cuenta=ui->NumCuentalineEdit->text();
    conn.connOpen();
    QSqlQuery qry(conn.mydb),qry2(conn.mydb),qry3(conn.mydb),qry4(conn.mydb),qry5(conn.mydb);
    qry.prepare("update cuenta set activo = '0' where num_cuenta = '"+num_cuenta+"'");
    qry2.prepare("update seguros set activo = '0' where num_cuenta = '"+num_cuenta+"'");
    qry3.prepare("update prestamo set activo = '0' where num_cuenta = '"+num_cuenta+"'");
    qry4.prepare("update inversion set activo = '0' where num_cuenta = '"+num_cuenta+"'");
    qry5.prepare("update credito_hipotecario set activo = '0' where num_cuenta = '"+num_cuenta+"'");
    if(qry.exec() && qry2.exec() && qry3.exec() && qry4.exec() && qry5.exec())
    {
        QMessageBox::information(this,tr("Desactivada"),tr("La cuenta del cliente a sido desactivada y todos sus servicios "));
        on_BuscarClientePushButton_clicked();
        ui->NumCuentalineEdit->clear();
        ui->SaldolineEdit->clear();
        ui->TipolineEdit->clear();
        ui->CodigoSeguridadlineEdit->clear();
        ui->FechTramitedateEdit->clearMaximumDate();
        ui->SaldolineEdit->setEnabled(true);
        ui->TipolineEdit->setEnabled(true);
        ui->AgregarCuentapushButton->setEnabled(true);
        ui->FechTramitedateEdit->setEnabled(true);
        ui->CancelarCuentapushButton->setEnabled(true);
        ui->GenerarCodigoSeguridadpushButton->setEnabled(true);
        ui->GenerarNumCuentapushButton->setEnabled(true);
        ui->DesactivarCuentapushButton->setEnabled(false);
        ui->ActivarCuentapushButton->setEnabled(false);

      //  conn.connClose();
     }
     else
        QMessageBox::critical(this, "Error","No se pudo dar de Baja");
}





void MainWindow4::on_AgregarSegurospushButton_clicked()
{
    //int x=1;
    QString empresa, descuento, moneda, importe_prima_anual, cobertura, suma_asegurada, plazo_seguro, plazo_pago, num_cuenta;
    empresa = ui->EmpresalineEdit->text();
    descuento = ui->DescuentolineEdit->text();
    moneda = ui->MonedalineEdit->text();
    importe_prima_anual = ui->ImportePrimaAnlineEdit->text();
    cobertura = ui->CoberturalineEdit->text();
    suma_asegurada=ui->SumaAseguradalineEdit->text();
    plazo_seguro = ui->PlazoSegurolineEdit->text();
    plazo_pago = ui->PlazoPagolineEdit->text();
    num_cuenta = ui->BuscarCuentaSegurostalineEdit->text();
    bool Esc=false, Web=false;

    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("INSERT INTO seguros (importe_prima_anual, suma_asegurada, plazo_seguro ,plazo_pago, num_cuenta,activo) values ('"+importe_prima_anual+"', '"+suma_asegurada+"', '"+plazo_seguro+"', '"+plazo_pago+"', '"+num_cuenta+"','0')");

    if(qry.exec())
    {
        Esc=true;
    }
    conn.connOpenWeb();
    QSqlQuery qry2(conn.mydb);
    qry2.prepare("INSERT INTO seguro (empresa, descuento, moneda, cobertura, ID_Cuenta) values ('"+empresa+"', '"+descuento+"','"+moneda+"','"+cobertura+"','"+num_cuenta+"')");
    if(qry2.exec())
    {
        Web=true;
    }


    if(Esc && Web)
    {
        QMessageBox::information(this,tr("Agregando"),tr("     Los datos se agregaron a la Base de Datos     "));
        ui->BuscarCuentaSegurostalineEdit->clear();
        ui->EmpresalineEdit->clear();
        ui->DescuentolineEdit->clear();
        ui->MonedalineEdit->clear();
        ui->ImportePrimaAnlineEdit->clear();
        ui->CoberturalineEdit->clear();
        ui->SumaAseguradalineEdit->clear();
        ui->PlazoSegurolineEdit->clear();
        ui->PlazoPagolineEdit->clear();
        ui->BuscarCuentaSegurostalineEdit->clear();

        ui->EmpresalineEdit->setEnabled(false);
        ui->DescuentolineEdit->setEnabled(false);
        ui->MonedalineEdit->setEnabled(false);
        ui->ImportePrimaAnlineEdit->setEnabled(false);
        ui->CoberturalineEdit->setEnabled(false);
        ui->SumaAseguradalineEdit->setEnabled(false);
        ui->PlazoSegurolineEdit->setEnabled(false);
        ui->PlazoPagolineEdit->setEnabled(false);
        ui->AgregarSegurospushButton->setEnabled(false);
        ui->CancelarSegurospushButton->setEnabled(false);


        conn.connClose();
     }
     else
       QMessageBox::critical(this, "Error","Llena el formulario correctamente");
      //  QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    if(Web==false)
    {
        QMessageBox::critical(this, "Error","Error conexión Web");
    }
    if(Esc==false)
    {
        QMessageBox::critical(this, "Error","Error conexión Escritorio");
    }
}

void MainWindow4::on_BuscarCuentaSegurosPushButton_clicked()
{
    QString buscar=ui->BuscarCuentaSegurostalineEdit->text();
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery qry(conn.mydb),qry2(conn.mydb);
    bool x=false;
    if(PuestoUsuario=="Empleado" or PuestoUsuario=="empleado" or PuestoUsuario=="emp")
    {
        qry.prepare("SELECT cuenta.num_cuenta,cuenta.activo,cliente.id_suc FROM cuenta INNER JOIN cliente  ON cuenta.id_cliente=cliente.id_cliente  WHERE cuenta.activo='1' AND cuenta.num_cuenta='"+buscar+"' AND cliente.id_suc = '"+LocalActual+"'");
    }
    else
    {
        qry.prepare("SELECT cuenta.num_cuenta,cuenta.activo FROM cuenta  WHERE cuenta.activo='1' AND cuenta.num_cuenta='"+buscar+"'");
    }
    qry.exec();
    while( qry.next())
      {
        x=true;
        if(x==true){
        qry2.prepare("SELECT seguros.num_poliza,seguros.importe_prima_anual,seguros.suma_asegurada,seguros.plazo_seguro,seguros.plazo_pago,seguros.num_cuenta,cuenta.activo  FROM seguros  INNER JOIN cuenta  ON seguros.num_cuenta=cuenta.num_cuenta WHERE cuenta.num_cuenta='"+buscar+"'");
        qry2.exec();
        modal->setQuery(qry2);
        ui->SegurostableView->setModel(modal);
        ui->EmpresalineEdit->setEnabled(true);
        ui->DescuentolineEdit->setEnabled(true);
        ui->MonedalineEdit->setEnabled(true);
        ui->ImportePrimaAnlineEdit->setEnabled(true);
        ui->CoberturalineEdit->setEnabled(true);
        ui->SumaAseguradalineEdit->setEnabled(true);
        ui->PlazoSegurolineEdit->setEnabled(true);
        ui->PlazoPagolineEdit->setEnabled(true);
        ui->AgregarSegurospushButton->setEnabled(true);
        ui->CancelarSegurospushButton->setEnabled(true);
        ui->ActivarseguropushButton->setEnabled(false);
        ui->DesactivarseguropushButton->setEnabled(false);
        QMessageBox::information(this,tr("Cargando"),tr("Se encontro la cuenta del cliente en el sistema"));}
      }
      if(x==false){
          ui->EmpresalineEdit->setEnabled(false);
          ui->DescuentolineEdit->setEnabled(false);
          ui->MonedalineEdit->setEnabled(false);
          ui->ImportePrimaAnlineEdit->setEnabled(false);
          ui->CoberturalineEdit->setEnabled(false);
          ui->SumaAseguradalineEdit->setEnabled(false);
          ui->PlazoSegurolineEdit->setEnabled(false);
          ui->PlazoPagolineEdit->setEnabled(false);
          ui->AgregarSegurospushButton->setEnabled(false);
          ui->CancelarSegurospushButton->setEnabled(false);
          ui->ActivarseguropushButton->setEnabled(false);
          ui->DesactivarseguropushButton->setEnabled(false);
        //  QMessageBox::critical(this,tr("error::"),qry.lastError().text());
            QMessageBox::critical(this, "Error","*Verifica que el cuenta exista y este activa");
      }
}

void MainWindow4::on_ActivarseguropushButton_clicked()
{
    QString num_poliza;
    num_poliza=ui->NumPolizalineEdit->text();
    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("update seguros set activo = '1' where num_poliza = '"+num_poliza+"'");
    if(qry.exec())
    {
        QMessageBox::information(this,tr("Activada"),tr("El seguro del cliente a sido activado "));
        on_BuscarCuentaSegurosPushButton_clicked();
        ui->EmpresalineEdit->clear();
        ui->DescuentolineEdit->clear();
        ui->MonedalineEdit->clear();
        ui->ImportePrimaAnlineEdit->clear();
        ui->CoberturalineEdit->clear();
        ui->SumaAseguradalineEdit->clear();
        ui->PlazoSegurolineEdit->clear();
        ui->PlazoPagolineEdit->clear();
        ui->DesactivarCuentapushButton->setEnabled(false);
        ui->ActivarCuentapushButton->setEnabled(false);

      //  conn.connClose();
     }
     else
        QMessageBox::critical(this, "Error","No se pudo dar de alta");
}

void MainWindow4::on_SegurostableView_activated(const QModelIndex &index)
{
    QString val = ui->SegurostableView->model()->data(index).toString();
    QString num_poliza, empresa, descuento, moneda, importe_prima_anual, cobertura, suma_asegurada, plazo_seguro, plazo_pago, num_cuenta;
    num_poliza = ui->NumPolizalineEdit->text();
    empresa = ui->EmpresalineEdit->text();
    descuento = ui->DescuentolineEdit->text();
    moneda = ui->MonedalineEdit->text();
    importe_prima_anual = ui->ImportePrimaAnlineEdit->text();
    cobertura = ui->CoberturalineEdit->text();
    suma_asegurada=ui->SumaAseguradalineEdit->text();
    plazo_seguro = ui->PlazoSegurolineEdit->text();
    plazo_pago = ui->PlazoPagolineEdit->text();
    num_cuenta = ui->BuscarCuentaSegurostalineEdit->text();
    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("select * from seguros WHERE num_poliza='"+val+"'");

    if(qry.exec())
   {
         QMessageBox::information(this,tr("Alta o Baja"),tr("*Tabla desactivada"));
        while(qry.next())
        {
            ui->EmpresalineEdit->setText(qry.value(1).toString());
            ui->DescuentolineEdit->setText(qry.value(2).toString());
            ui->MonedalineEdit->setText(qry.value(3).toString());
            ui->ImportePrimaAnlineEdit->setText(qry.value(4).toString());
            ui->CoberturalineEdit->setText(qry.value(5).toString());
            ui->SumaAseguradalineEdit->setText(qry.value(6).toString());
            ui->PlazoSegurolineEdit->setText(qry.value(7).toString());
            ui->PlazoPagolineEdit->setText(qry.value(8).toString());
            ui->NumPolizalineEdit->setText(qry.value(0).toString());
            ui->EmpresalineEdit->setEnabled(false);
            ui->DescuentolineEdit->setEnabled(false);
            ui->MonedalineEdit->setEnabled(false);
            ui->ImportePrimaAnlineEdit->setEnabled(false);
            ui->CoberturalineEdit->setEnabled(false);
            ui->SumaAseguradalineEdit->setEnabled(false);
            ui->PlazoSegurolineEdit->setEnabled(false);
            ui->PlazoPagolineEdit->setEnabled(false);
            ui->AgregarSegurospushButton->setEnabled(false);
            ui->CancelarSegurospushButton->setEnabled(false);
            ui->ActivarseguropushButton->setEnabled(true);
            ui->DesactivarseguropushButton->setEnabled(true);
            ui->CancelarSegurospushButton->setEnabled(true);
        }
       // conn.connClose();
     }
     else
    {
        QMessageBox::critical(this, "Error","No se cargaron los datos");
         //QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}

void MainWindow4::on_DesactivarseguropushButton_clicked()
{
    QString num_poliza;
    num_poliza=ui->NumPolizalineEdit->text();
    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("update seguros set activo = '0' where num_poliza = '"+num_poliza+"'");
    if(qry.exec())
    {
        QMessageBox::information(this,tr("Desactivada"),tr("El seguro del cliente a sido desactivado "));
        on_BuscarCuentaSegurosPushButton_clicked();
        ui->EmpresalineEdit->clear();
        ui->DescuentolineEdit->clear();
        ui->MonedalineEdit->clear();
        ui->NumPolizalineEdit->clear();
        ui->ImportePrimaAnlineEdit->clear();
        ui->CoberturalineEdit->clear();
        ui->SumaAseguradalineEdit->clear();
        ui->PlazoSegurolineEdit->clear();
        ui->PlazoPagolineEdit->clear();
        ui->DesactivarCuentapushButton->setEnabled(false);
        ui->ActivarCuentapushButton->setEnabled(false);

      //  conn.connClose();
     }
     else
        QMessageBox::critical(this, "Error","No se pudo dar de alta");
}

void MainWindow4::on_CancelarSegurospushButton_clicked()
{
    ui->EmpresalineEdit->clear();
    ui->DescuentolineEdit->clear();
    ui->MonedalineEdit->clear();
    ui->ImportePrimaAnlineEdit->clear();
    ui->CoberturalineEdit->clear();
    ui->SumaAseguradalineEdit->clear();
    ui->PlazoSegurolineEdit->clear();
    ui->PlazoPagolineEdit->clear();
    ui->EmpresalineEdit->setEnabled(false);
    ui->DescuentolineEdit->setEnabled(false);
    ui->MonedalineEdit->setEnabled(false);
    ui->ImportePrimaAnlineEdit->setEnabled(false);
    ui->CoberturalineEdit->setEnabled(false);
    ui->SumaAseguradalineEdit->setEnabled(false);
    ui->PlazoSegurolineEdit->setEnabled(false);
    ui->PlazoPagolineEdit->setEnabled(false);
    ui->AgregarSegurospushButton->setEnabled(false);
    ui->CancelarSegurospushButton->setEnabled(false);
    ui->ActivarseguropushButton->setEnabled(true);
    ui->DesactivarseguropushButton->setEnabled(true);
    ui->CancelarSegurospushButton->setEnabled(true);
    conn.connClose();

}

void MainWindow4::on_AgregarPrestamopushButton_clicked()
{
    //int x=1;
    QString id_prestamo,tipo, fecha_aceptacion, mensualidad, periodo_prestamo,tasa_interes, total, num_cuenta;
    id_prestamo=ui->IDPrestamolineEdit->text();
    tipo = ui->TipoPrestamolineEdit->text();
    fecha_aceptacion = ui->FechaAcepdateEdit->text();
    mensualidad = ui->MensualidadPrestamolineEdit->text();
    periodo_prestamo = ui->PeriodoPrestamolineEdit->text();
    tasa_interes = ui->TasaInteresPrestamolineEdit->text();
    total = ui->TotalPrestamolineEdit->text();
    num_cuenta=ui->BuscarPrestamosCuentalineEdit->text();
    bool Esc=false,Web=false;
    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("INSERT INTO prestamo (mensualidad, total, num_cuenta, activo) values ('"+mensualidad+"', '"+total+"', '"+num_cuenta+"','1')");
    if(qry.exec())
    {
        Esc=true;
    }
    conn.connOpenWeb();
    QSqlQuery qry2(conn.mydb);
    qry2.prepare("INSERT INTO prestamo (tipo, fecha_de_aceptacion, periodo_del_prestamo, tasa_de_interes, ID_Cuenta) values ('"+tipo+"','"+fecha_aceptacion+"', '"+periodo_prestamo+"','"+tasa_interes+"', '"+num_cuenta+"')");
    if(qry2.exec())
    {
        Web=true;
    }
    if(Esc && Web)
    {
        QMessageBox::information(this,tr("Agregando"),tr("     Los datos se agregaron a la Base de Datos     "));
        ui->IDPrestamolineEdit->clear();
        ui->TipoPrestamolineEdit->clear();
        ui->FechaAcepdateEdit->clearMaximumDate();
        ui->MensualidadPrestamolineEdit->clear();
        ui->PeriodoPrestamolineEdit->clear();
        ui->TasaInteresPrestamolineEdit->clear();
        ui->TotalPrestamolineEdit->clear();
        ui->BuscarPrestamosCuentalineEdit->clear();

        ui->IDPrestamolineEdit->setEnabled(false);
        ui->TipoPrestamolineEdit->setEnabled(false);
        ui->FechaAcepdateEdit->setEnabled(false);
        ui->MensualidadPrestamolineEdit->setEnabled(false);
        ui->PeriodoPrestamolineEdit->setEnabled(false);
        ui->TasaInteresPrestamolineEdit->setEnabled(false);
        ui->TotalPrestamolineEdit->setEnabled(false);
        ui->AgregarPrestamopushButton->setEnabled(false);
        ui->CancelarPrestamopushButton->setEnabled(false);
        ui->ActivarPrestamopushButton->setEnabled(false);
        ui->DesactivarPrestamopushButton->setEnabled(false);



        conn.connClose();
     }
     else
       QMessageBox::critical(this, "Error","Llena el formulario correctamente");
       // QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    if(Web==false)
    {
        QMessageBox::critical(this, "Error","Error conexión Web");
    }
    if(Esc==false)
    {
        QMessageBox::critical(this, "Error","Error conexión Escritorio");
    }

}

void MainWindow4::on_BuscarPrestamosCuentPushButton_clicked()
{
    QString buscar=ui->BuscarPrestamosCuentalineEdit->text();
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    QSqlQuery qry2(conn.mydb);
    bool x=false;
    if(PuestoUsuario=="Empleado" or PuestoUsuario=="empleado" or PuestoUsuario=="emp")
    {
        qry.prepare("SELECT cuenta.num_cuenta,cuenta.activo,cliente.id_suc FROM cuenta INNER JOIN cliente  ON cuenta.id_cliente=cliente.id_cliente  WHERE cuenta.activo='1' AND cuenta.num_cuenta='"+buscar+"' AND cliente.id_suc = '"+LocalActual+"'");
    }
    else
    {
        qry.prepare("SELECT cuenta.num_cuenta,cuenta.activo FROM cuenta  WHERE cuenta.activo='1' AND cuenta.num_cuenta='"+buscar+"'");
    }
    qry.exec();
    while( qry.next())
      {
        x=true;
        if(x==true){
        qry2.prepare("SELECT prestamo.id_prestamo,prestamo.activo,prestamo.mensualidad,prestamo.total,cuenta.num_cuenta,cuenta.activo  FROM prestamo  INNER JOIN cuenta  ON prestamo.num_cuenta=cuenta.num_cuenta WHERE cuenta.num_cuenta='"+buscar+"'");
        qry2.exec();
        modal->setQuery(qry2);
        ui->PrestamotableView->setModel(modal);
        ui->IDPrestamolineEdit->setEnabled(true);
        ui->TipoPrestamolineEdit->setEnabled(true);
        ui->FechaAcepdateEdit->setEnabled(true);
        ui->MensualidadPrestamolineEdit->setEnabled(true);
        ui->PeriodoPrestamolineEdit->setEnabled(true);
        ui->TasaInteresPrestamolineEdit->setEnabled(true);
        ui->TotalPrestamolineEdit->setEnabled(true);
        ui->AgregarPrestamopushButton->setEnabled(true);
        ui->CancelarPrestamopushButton->setEnabled(true);
        ui->ActivarPrestamopushButton->setEnabled(false);
        ui->DesactivarPrestamopushButton->setEnabled(false);
        //ui->pushButton_3->setEnabled(true);
        QMessageBox::information(this,tr("Cargando"),tr("Se encontro la cuenta del cliente en el sistema"));}
      }
      if(x==false){
          ui->IDPrestamolineEdit->setEnabled(false);
          ui->TipoPrestamolineEdit->setEnabled(false);
          ui->FechaAcepdateEdit->setEnabled(false);
          ui->MensualidadPrestamolineEdit->setEnabled(false);
          ui->PeriodoPrestamolineEdit->setEnabled(false);
          ui->TasaInteresPrestamolineEdit->setEnabled(false);
          ui->TotalPrestamolineEdit->setEnabled(false);
          ui->AgregarPrestamopushButton->setEnabled(false);
          ui->CancelarPrestamopushButton->setEnabled(false);
          ui->ActivarPrestamopushButton->setEnabled(false);
          ui->DesactivarPrestamopushButton->setEnabled(false);
          //ui->pushButton_3->setEnabled(false);
        // QMessageBox::critical(this,tr("error::"),qry.lastError().text());
          QMessageBox::critical(this, "Error","*Verifica que la cuenta exista y este activa");
      }
}

void MainWindow4::on_PrestamotableView_activated(const QModelIndex &index)
{
    QString val = ui->PrestamotableView->model()->data(index).toString();
    QString id_prestamo,tipo, fecha_aceptacion, mensualidad, periodo_prestamo,tasa_interes, total, num_cuenta;
    id_prestamo=ui->IDPrestamolineEdit->text();
    tipo = ui->TipoPrestamolineEdit->text();
    fecha_aceptacion = ui->FechaAcepdateEdit->text();
    mensualidad = ui->MensualidadPrestamolineEdit->text();
    periodo_prestamo = ui->PeriodoPrestamolineEdit->text();
    tasa_interes = ui->TasaInteresPrestamolineEdit->text();
    total = ui->TotalPrestamolineEdit->text();
    num_cuenta=ui->BuscarPrestamosCuentalineEdit->text();

    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("select * from prestamo WHERE id_prestamo='"+val+"'");

    if(qry.exec())
   {
         QMessageBox::information(this,tr("Alta o Baja"),tr("*Tabla desactivada"));
        while(qry.next())
        {
            ui->IDPrestamolineEdit->setText(qry.value(0).toString());
            ui->TipoPrestamolineEdit->setText(qry.value(1).toString());
            ui->FechaAcepdateEdit->setDate(qry.value(2).toDate());
            ui->MensualidadPrestamolineEdit->setText(qry.value(3).toString());
            ui->PeriodoPrestamolineEdit->setText(qry.value(4).toString());
            ui->TasaInteresPrestamolineEdit->setText(qry.value(5).toString());
            ui->TotalPrestamolineEdit->setText(qry.value(6).toString());

           // ui->IDPrestamolineEdit->setEnabled(false);
            ui->TipoPrestamolineEdit->setEnabled(false);
            ui->FechaAcepdateEdit->setEnabled(false);
            ui->MensualidadPrestamolineEdit->setEnabled(false);
            ui->PeriodoPrestamolineEdit->setEnabled(false);
            ui->TasaInteresPrestamolineEdit->setEnabled(false);
            ui->TotalPrestamolineEdit->setEnabled(false);
            ui->AgregarPrestamopushButton->setEnabled(false);
            ui->CancelarPrestamopushButton->setEnabled(true);
            ui->ActivarPrestamopushButton->setEnabled(true);
            ui->DesactivarPrestamopushButton->setEnabled(true);
        }
       // conn.connClose();
     }
     else
    {
        QMessageBox::critical(this, "Error","No se cargaron los datos");
        // QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }

}

void MainWindow4::on_ActivarPrestamopushButton_clicked()
{
    QString id_prestamo;
    id_prestamo=ui->IDPrestamolineEdit->text();
    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("update prestamo set activo = '1' where id_prestamo = '"+id_prestamo+"'");
    if(qry.exec())
    {
        QMessageBox::information(this,tr("Activada"),tr("El prestamo del cliente a sido activado "));
        on_BuscarPrestamosCuentPushButton_clicked();
        ui->IDPrestamolineEdit->clear();
        ui->TipoPrestamolineEdit->clear();
        ui->FechaAcepdateEdit->clearMaximumDate();
        ui->MensualidadPrestamolineEdit->clear();
        ui->PeriodoPrestamolineEdit->clear();
        ui->TasaInteresPrestamolineEdit->clear();
        ui->TotalPrestamolineEdit->clear();
        ui->IDPrestamolineEdit->setEnabled(true);
        ui->TipoPrestamolineEdit->setEnabled(true);
        ui->FechaAcepdateEdit->setEnabled(true);
        ui->MensualidadPrestamolineEdit->setEnabled(true);
        ui->PeriodoPrestamolineEdit->setEnabled(true);
        ui->TasaInteresPrestamolineEdit->setEnabled(true);
        ui->TotalPrestamolineEdit->setEnabled(true);
        ui->CancelarPrestamopushButton->setEnabled(true);
        ui->ActivarPrestamopushButton->setEnabled(false);
        ui->DesactivarPrestamopushButton->setEnabled(false);

      //  conn.connClose();
     }
     else
        QMessageBox::critical(this, "Error","No se pudo dar de alta");
}

void MainWindow4::on_DesactivarPrestamopushButton_clicked()
{
    QString id_prestamo;
    id_prestamo=ui->IDPrestamolineEdit->text();
    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("update prestamo set activo = '0' where id_prestamo = '"+id_prestamo+"'");
    if(qry.exec())
    {
        QMessageBox::information(this,tr("Desactivada"),tr("El prestamo del cliente a sido desactivado "));
        on_BuscarPrestamosCuentPushButton_clicked();
        ui->IDPrestamolineEdit->clear();
        ui->TipoPrestamolineEdit->clear();
        ui->FechaAcepdateEdit->clearMaximumDate();
        ui->MensualidadPrestamolineEdit->clear();
        ui->PeriodoPrestamolineEdit->clear();
        ui->TasaInteresPrestamolineEdit->clear();
        ui->TotalPrestamolineEdit->clear();
        ui->IDPrestamolineEdit->setEnabled(true);
        ui->TipoPrestamolineEdit->setEnabled(true);
        ui->FechaAcepdateEdit->setEnabled(true);
        ui->MensualidadPrestamolineEdit->setEnabled(true);
        ui->PeriodoPrestamolineEdit->setEnabled(true);
        ui->TasaInteresPrestamolineEdit->setEnabled(true);
        ui->TotalPrestamolineEdit->setEnabled(true);
        ui->CancelarPrestamopushButton->setEnabled(true);
        ui->ActivarPrestamopushButton->setEnabled(false);
        ui->DesactivarPrestamopushButton->setEnabled(false);

      //  conn.connClose();
     }
     else
        QMessageBox::critical(this, "Error","No se pudo dar de baja");
}

void MainWindow4::on_CancelarPrestamopushButton_clicked()
{
    ui->IDPrestamolineEdit->clear();
    ui->TipoPrestamolineEdit->clear();
    ui->FechaAcepdateEdit->clearMaximumDate();
    ui->MensualidadPrestamolineEdit->clear();
    ui->PeriodoPrestamolineEdit->clear();
    ui->TasaInteresPrestamolineEdit->clear();
    ui->TotalPrestamolineEdit->clear();
    ui->BuscarPrestamosCuentalineEdit->clear();

    ui->IDPrestamolineEdit->setEnabled(false);
    ui->TipoPrestamolineEdit->setEnabled(false);
    ui->FechaAcepdateEdit->setEnabled(false);
    ui->MensualidadPrestamolineEdit->setEnabled(false);
    ui->PeriodoPrestamolineEdit->setEnabled(false);
    ui->TasaInteresPrestamolineEdit->setEnabled(false);
    ui->TotalPrestamolineEdit->setEnabled(false);
    ui->AgregarPrestamopushButton->setEnabled(false);
    ui->CancelarPrestamopushButton->setEnabled(false);
    ui->ActivarPrestamopushButton->setEnabled(false);
    ui->DesactivarPrestamopushButton->setEnabled(false);
    conn.connClose();

}

void MainWindow4::on_AgregarInversionpushButton_clicked()
{
    //int x=1;
    QString id_inversion,tipo, cantidad_invertida, tasa_interes, tipo_tasa,plazo, num_cuenta;
    id_inversion=ui->IDInversionlineEdit->text();
    tipo = ui->TipoInversionlineEdit->text();
    cantidad_invertida = ui->CantidadInvertidaInversionlineEdit->text();
    tasa_interes = ui->TasaInteresInversionlineEdit->text();
    tipo_tasa = ui->TipoTasaInversionlineEdit->text();
    plazo = ui->PlazoInversionlineEdit->text();
    num_cuenta=ui->BuscarInversionCuentalineEdit->text();
    bool Esc=false, Web=false;

    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("INSERT INTO inversion (cantidad_invertida, plazo, num_cuenta,activo) values ('"+cantidad_invertida+"','"+plazo+"','"+num_cuenta+"','0')");

    if(qry.exec())
    {
        Esc=true;
    }
    conn.connOpenWeb();
    QSqlQuery qry2(conn.mydb);
    qry2.prepare("INSERT INTO inversion (tipo, tipo_de_tasa, tasa_de_interes,ID_Cuenta) values ('"+tipo+"','"+tipo_tasa+"','"+tasa_interes+"','"+num_cuenta+"')");
    if(qry2.exec())
    {
        Web=true;
    }


    if(Esc && Web)
    {
        QMessageBox::information(this,tr("Agregando"),tr("     Los datos se agregaron a la Base de Datos     "));
        ui->IDInversionlineEdit->clear();
        ui->TipoInversionlineEdit->clear();
        ui->CantidadInvertidaInversionlineEdit->clear();
        ui->TasaInteresInversionlineEdit->clear();
        ui->TipoTasaInversionlineEdit->clear();
        ui->PlazoInversionlineEdit->clear();
        ui->BuscarInversionCuentalineEdit->clear();
        ui->AgregarInversionpushButton->setEnabled(false);
        ui->CancelarInversionpushButton->setEnabled(false);

        conn.connClose();
     }
     else
       QMessageBox::critical(this, "Error","Llena el formulario correctamente");
       // QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    if(Web==false)
    {
        QMessageBox::critical(this, "Error","Error conexión Web");
    }
    if(Esc==false)
    {
        QMessageBox::critical(this, "Error","Error conexión Escritorio");
    }
}

void MainWindow4::on_BuscarcuentaInversionPushButton_clicked()
{
    QString buscar=ui->BuscarInversionCuentalineEdit->text();
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery qry(conn.mydb),qry2(conn.mydb);
    bool x=false;
    if(PuestoUsuario=="Empleado" or PuestoUsuario=="empleado" or PuestoUsuario=="emp")
    {
        qry.prepare("SELECT cuenta.num_cuenta,cuenta.activo,cliente.id_suc FROM cuenta INNER JOIN cliente  ON cuenta.id_cliente=cliente.id_cliente  WHERE cuenta.activo='1' AND cuenta.num_cuenta='"+buscar+"' AND cliente.id_suc = '"+LocalActual+"'");
    }
    else
    {
        qry.prepare("SELECT cuenta.num_cuenta,cuenta.activo FROM cuenta  WHERE cuenta.activo='1' AND cuenta.num_cuenta='"+buscar+"'");
    }
    qry.exec();
    while( qry.next())
      {
        x=true;
        if(x==true){
        qry2.prepare("SELECT inversion.id_inversion,inversion.activo,inversion.cantidad_invertida, inversion.plazo,cuenta.num_cuenta FROM inversion  INNER JOIN cuenta  ON inversion.num_cuenta=cuenta.num_cuenta WHERE cuenta.num_cuenta='"+buscar+"'");
        qry2.exec();
        modal->setQuery(qry2);
        ui->InversiontableView->setModel(modal);
        //ui->IDInversionlineEdit->setEnabled(true);
        ui->TipoInversionlineEdit->setEnabled(true);
        ui->CantidadInvertidaInversionlineEdit->setEnabled(true);
        ui->TasaInteresInversionlineEdit->setEnabled(true);
        ui->TipoTasaInversionlineEdit->setEnabled(true);
        ui->PlazoInversionlineEdit->setEnabled(true);
        ui->AgregarInversionpushButton->setEnabled(true);
        ui->CancelarInversionpushButton->setEnabled(true);
        //ui->pushButton_4->setEnabled(true);
        ui->ActivarInversionpushButton->setEnabled(false);
        ui->DesactivarInversionpushButton->setEnabled(false);
        QMessageBox::information(this,tr("Cargando"),tr("Se encontro la cuenta del cliente en el sistema"));}
      }
      if(x==false){
          //ui->IDInversionlineEdit->setEnabled(false);
          ui->TipoInversionlineEdit->setEnabled(false);
          ui->CantidadInvertidaInversionlineEdit->setEnabled(false);
          ui->TasaInteresInversionlineEdit->setEnabled(false);
          ui->TipoTasaInversionlineEdit->setEnabled(false);
          ui->PlazoInversionlineEdit->setEnabled(false);
          ui->AgregarInversionpushButton->setEnabled(false);
          ui->CancelarInversionpushButton->setEnabled(false);
          ui->ActivarInversionpushButton->setEnabled(false);
          ui->DesactivarInversionpushButton->setEnabled(false);
          //ui->pushButton_4->setEnabled(false);
         //QMessageBox::critical(this,tr("error::"),qry.lastError().text());
          QMessageBox::critical(this, "Error","*Verifica que la cuenta exista y este activa");
      }
}

void MainWindow4::on_InversiontableView_activated(const QModelIndex &index)
{
    QString val = ui->InversiontableView->model()->data(index).toString();
    QString id_inversion,tipo, cantidad_invertida, tasa_interes, tipo_tasa,plazo, num_cuenta;
   // id_inversion=ui->IDInversionlineEdit->text();
    tipo = ui->TipoInversionlineEdit->text();
    cantidad_invertida = ui->CantidadInvertidaInversionlineEdit->text();
    tasa_interes = ui->TasaInteresInversionlineEdit->text();
    tipo_tasa = ui->TipoTasaInversionlineEdit->text();
    plazo = ui->PlazoInversionlineEdit->text();
    num_cuenta=ui->BuscarInversionCuentalineEdit->text();

    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("select * from inversion WHERE id_inversion='"+val+"'");

    if(qry.exec())
   {
         QMessageBox::information(this,tr("Alta o Baja"),tr("*Tabla desactivada"));
        while(qry.next())
        {
            //ui->IDInversionlineEdit->setText(qry.value(0).toString());
            ui->TipoInversionlineEdit->setText(qry.value(1).toString());
            ui->CantidadInvertidaInversionlineEdit->setText(qry.value(2).toString());
            ui->TasaInteresInversionlineEdit->setText(qry.value(3).toString());
            ui->TipoTasaInversionlineEdit->setText(qry.value(4).toString());
            ui->PlazoInversionlineEdit->setText(qry.value(5).toString());

           // ui->IDInversionlineEdit->setEnabled(false);
            ui->TipoInversionlineEdit->setEnabled(false);
            ui->CantidadInvertidaInversionlineEdit->setEnabled(false);
            ui->TasaInteresInversionlineEdit->setEnabled(false);
            ui->TipoTasaInversionlineEdit->setEnabled(false);
            ui->PlazoInversionlineEdit->setEnabled(false);
            ui->AgregarInversionpushButton->setEnabled(false);
            ui->CancelarInversionpushButton->setEnabled(true);
            ui->ActivarInversionpushButton->setEnabled(true);
            ui->DesactivarInversionpushButton->setEnabled(true);
        }
       // conn.connClose();
     }
     else
    {
        QMessageBox::critical(this, "Error","No se cargaron los datos");
        // QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }

}

void MainWindow4::on_ActivarInversionpushButton_clicked()
{
    QString id_inversion;
   // id_inversion=ui->IDInversionlineEdit->text();
    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("update inversion set activo = '1' where id_inversion = '"+id_inversion+"'");
    if(qry.exec())
    {
        QMessageBox::information(this,tr("Activada"),tr("La inversion del cliente a sido activada "));
        on_BuscarcuentaInversionPushButton_clicked();
       // ui->IDInversionlineEdit->clear();
        ui->TipoInversionlineEdit->clear();
        ui->CantidadInvertidaInversionlineEdit->clear();
        ui->TasaInteresInversionlineEdit->clear();
        ui->TipoTasaInversionlineEdit->clear();
        ui->PlazoInversionlineEdit->clear();

       // ui->IDInversionlineEdit->setEnabled(true);
        ui->TipoInversionlineEdit->setEnabled(true);
        ui->CantidadInvertidaInversionlineEdit->setEnabled(true);
        ui->TasaInteresInversionlineEdit->setEnabled(true);
        ui->TipoTasaInversionlineEdit->setEnabled(true);
        ui->PlazoInversionlineEdit->setEnabled(true);
        ui->AgregarInversionpushButton->setEnabled(true);
        ui->CancelarInversionpushButton->setEnabled(true);
        ui->ActivarInversionpushButton->setEnabled(false);
        ui->DesactivarInversionpushButton->setEnabled(false);

      //  conn.connClose();
     }
     else
        QMessageBox::critical(this, "Error","No se pudo dar de alta");
}

void MainWindow4::on_DesactivarInversionpushButton_clicked()
{
    QString id_inversion;
   // id_inversion=ui->IDInversionlineEdit->text();
    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("update inversion set activo = '0' where id_inversion = '"+id_inversion+"'");
    if(qry.exec())
    {
        QMessageBox::information(this,tr("Desactivada"),tr("La inversion del cliente a sido desactivada "));
        on_BuscarcuentaInversionPushButton_clicked();
      //  ui->IDInversionlineEdit->clear();
        ui->TipoInversionlineEdit->clear();
        ui->CantidadInvertidaInversionlineEdit->clear();
        ui->TasaInteresInversionlineEdit->clear();
        ui->TipoTasaInversionlineEdit->clear();
        ui->PlazoInversionlineEdit->clear();

       // ui->IDInversionlineEdit->setEnabled(true);
        ui->TipoInversionlineEdit->setEnabled(true);
        ui->CantidadInvertidaInversionlineEdit->setEnabled(true);
        ui->TasaInteresInversionlineEdit->setEnabled(true);
        ui->TipoTasaInversionlineEdit->setEnabled(true);
        ui->PlazoInversionlineEdit->setEnabled(true);
        ui->AgregarInversionpushButton->setEnabled(true);
        ui->CancelarInversionpushButton->setEnabled(true);
        ui->ActivarInversionpushButton->setEnabled(false);
        ui->DesactivarInversionpushButton->setEnabled(false);

      //  conn.connClose();
     }
     else
        QMessageBox::critical(this, "Error","No se pudo dar de baja");
}

void MainWindow4::on_CancelarInversionpushButton_clicked()
{
    //ui->IDInversionlineEdit->clear();
    ui->TipoInversionlineEdit->clear();
    ui->CantidadInvertidaInversionlineEdit->clear();
    ui->TasaInteresInversionlineEdit->clear();
    ui->TipoTasaInversionlineEdit->clear();
    ui->PlazoInversionlineEdit->clear();
    ui->BuscarInversionCuentalineEdit->clear();

    //ui->IDInversionlineEdit->setEnabled(false);
    ui->TipoInversionlineEdit->setEnabled(false);
    ui->CantidadInvertidaInversionlineEdit->setEnabled(false);
    ui->TasaInteresInversionlineEdit->setEnabled(false);
    ui->TipoTasaInversionlineEdit->setEnabled(false);
    ui->PlazoInversionlineEdit->setEnabled(false);
    ui->AgregarInversionpushButton->setEnabled(false);
    ui->CancelarInversionpushButton->setEnabled(false);
    ui->ActivarInversionpushButton->setEnabled(false);
    ui->DesactivarInversionpushButton->setEnabled(false);
    conn.connClose();

}

void MainWindow4::on_AgregarCreditoHpushButton_clicked()
{
    //int x=1;
    QString id_credito,periodo_pago, mensualidad, total, tasa_interes,monto_prima, valor_inmueble, num_cuenta;
    //id_credito=ui->IDcreditoHipotecariolineEdit->text();
    periodo_pago = ui->PeriodoPagoCHlineEdit->text();
    mensualidad = ui->MensualidadCHlineEdit->text();
    total = ui->TotalCHlineEdit->text();
    tasa_interes = ui->TasaInteresCHlineEdit->text();
    monto_prima = ui->MontoPrimaCHlineEdit->text();
    valor_inmueble = ui->ValorInmuebleCHlineEdit->text();
    num_cuenta=ui->BuscarHipotecariosCuentalineEdit->text();
    bool Esc=false, Web=false;

    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("INSERT INTO credito_hipotecario (mensualidad, total, monto_prima, valor_inmueble, num_cuenta,activo) values ('"+mensualidad+"', '"+total+"','"+monto_prima+"', '"+valor_inmueble+"', '"+num_cuenta+"','1')");
    if(qry.exec())
    {
        Esc=true;
    }
    conn.connOpenWeb();
    QSqlQuery qry2(conn.mydb);
    qry2.prepare("INSERT INTO credito_hipotecario (periodo_de_pago, tasa_de_interes, ID_Cuenta) values ('"+periodo_pago+"','"+tasa_interes+"','"+num_cuenta+"')");
    if(qry2.exec())
    {
        Web=true;
    }
    if(Esc && Web)
    {
        QMessageBox::information(this,tr("Agregando"),tr("     Los datos se agregaron a la Base de Datos     "));
        //ui->IDcreditoHipotecariolineEdit->clear();
        ui->PeriodoPagoCHlineEdit->clear();
        ui->MensualidadCHlineEdit->clear();
        ui->TotalCHlineEdit->clear();
        ui->TasaInteresCHlineEdit->clear();
        ui->MontoPrimaCHlineEdit->clear();
        ui->ValorInmuebleCHlineEdit->clear();
        ui->BuscarHipotecariosCuentalineEdit->clear();

        //ui->IDcreditoHipotecariolineEdit->setEnabled(false);
        ui->PeriodoPagoCHlineEdit->setEnabled(false);
        ui->MensualidadCHlineEdit->setEnabled(false);
        ui->TotalCHlineEdit->setEnabled(false);
        ui->TasaInteresCHlineEdit->setEnabled(false);
        ui->MontoPrimaCHlineEdit->setEnabled(false);
        ui->ValorInmuebleCHlineEdit->setEnabled(false);
        ui->AgregarCreditoHpushButton->setEnabled(false);
        ui->CancelarCreditopushButton->setEnabled(false);
        ui->ActivarCreditopushButton->setEnabled(false);
        ui->DesactivarCreditopushButton->setEnabled(false);


        conn.connClose();
     }
     else
       QMessageBox::critical(this, "Error","Llena el formulario correctamente");
        //QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    if(Web==false)
    {
        QMessageBox::critical(this, "Error","Error conexión Web");
    }
    if(Esc==false)
    {
        QMessageBox::critical(this, "Error","Error conexión Escritorio");
    }
}

void MainWindow4::on_BuscarHipotecasCuentaPushButton_clicked()
{
    QString buscar=ui->BuscarHipotecariosCuentalineEdit->text();
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery qry(conn.mydb),qry2(conn.mydb);
    bool x=false;
    if(PuestoUsuario=="Empleado" or PuestoUsuario=="empleado" or PuestoUsuario=="emp")
    {
        qry.prepare("SELECT cuenta.num_cuenta,cuenta.activo,cliente.id_suc FROM cuenta INNER JOIN cliente  ON cuenta.id_cliente=cliente.id_cliente  WHERE cuenta.activo='1' AND cuenta.num_cuenta='"+buscar+"' AND cliente.id_suc = '"+LocalActual+"'");
    }
    else
    {
        qry.prepare("SELECT cuenta.num_cuenta,cuenta.activo FROM cuenta  WHERE cuenta.activo='1' AND cuenta.num_cuenta='"+buscar+"'");
    }
    qry.exec();
    while( qry.next())
      {
        x=true;
        if(x==true){
        qry2.prepare("SELECT credito_hipotecario.id_credito, credito_hipotecario.activo ,credito_hipotecario.total,credito_hipotecario.monto_prima,credito_hipotecario.valor_inmueble,cuenta.num_cuenta,cuenta.activo  FROM credito_hipotecario  INNER JOIN cuenta  ON credito_hipotecario.num_cuenta=cuenta.num_cuenta WHERE cuenta.num_cuenta='"+buscar+"'");
        qry2.exec();
        modal->setQuery(qry2);
        ui->CreditoHipotecariotableView->setModel(modal);
        //ui->IDcreditoHipotecariolineEdit->setEnabled(true);
        ui->PeriodoPagoCHlineEdit->setEnabled(true);
        ui->MensualidadCHlineEdit->setEnabled(true);
        ui->TotalCHlineEdit->setEnabled(true);
        ui->TasaInteresCHlineEdit->setEnabled(true);
        ui->MontoPrimaCHlineEdit->setEnabled(true);
        ui->ValorInmuebleCHlineEdit->setEnabled(true);
        ui->AgregarCreditoHpushButton->setEnabled(true);
        ui->CancelarCreditopushButton->setEnabled(true);
        ui->ActivarCreditopushButton->setEnabled(false);
        ui->DesactivarCreditopushButton->setEnabled(false);
       // ui->pushButton_2->setEnabled(true);
        QMessageBox::information(this,tr("Cargando"),tr("Se encontro la cuenta del cliente en el sistema"));}
      }
      if(x==false){
          //ui->IDcreditoHipotecariolineEdit->setEnabled(false);
          ui->PeriodoPagoCHlineEdit->setEnabled(false);
          ui->MensualidadCHlineEdit->setEnabled(false);
          ui->TotalCHlineEdit->setEnabled(false);
          ui->TasaInteresCHlineEdit->setEnabled(false);
          ui->MontoPrimaCHlineEdit->setEnabled(false);
          ui->ValorInmuebleCHlineEdit->setEnabled(false);
          ui->AgregarCreditoHpushButton->setEnabled(false);
          ui->CancelarCreditopushButton->setEnabled(false);
          ui->ActivarCreditopushButton->setEnabled(false);
          ui->DesactivarCreditopushButton->setEnabled(false);
         // ui->pushButton_2->setEnabled(false);
        //QMessageBox::critical(this,tr("error::"),qry.lastError().text());
          QMessageBox::critical(this, "Error","*Verifica que la cuenta exista y este activa");
      }
}

void MainWindow4::on_CreditoHipotecariotableView_activated(const QModelIndex &index)
{
    QString val = ui->CreditoHipotecariotableView->model()->data(index).toString();
    QString id_credito,periodo_pago, mensualidad, total, tasa_interes,monto_prima, valor_inmueble, num_cuenta;
    //id_credito=ui->IDcreditoHipotecariolineEdit->text();
    periodo_pago = ui->PeriodoPagoCHlineEdit->text();
    mensualidad = ui->MensualidadCHlineEdit->text();
    total = ui->TotalCHlineEdit->text();
    tasa_interes = ui->TasaInteresCHlineEdit->text();
    monto_prima = ui->MontoPrimaCHlineEdit->text();
    valor_inmueble = ui->ValorInmuebleCHlineEdit->text();
    num_cuenta=ui->BuscarHipotecariosCuentalineEdit->text();

    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("select * from credito_hipotecario WHERE id_credito='"+val+"'");

    if(qry.exec())
   {
         QMessageBox::information(this,tr("Alta o Baja"),tr("*Tabla desactivada"));
        while(qry.next())
        {
           // ui->IDcreditoHipotecariolineEdit->setText(qry.value(0).toString());
            ui->PeriodoPagoCHlineEdit->setText(qry.value(1).toString());
            ui->MensualidadCHlineEdit->setText(qry.value(2).toString());
            ui->TotalCHlineEdit->setText(qry.value(3).toString());
            ui->TasaInteresCHlineEdit->setText(qry.value(4).toString());
            ui->MontoPrimaCHlineEdit->setText(qry.value(5).toString());
            ui->ValorInmuebleCHlineEdit->setText(qry.value(6).toString());

            //ui->IDcreditoHipotecariolineEdit->setEnabled(false);
            ui->PeriodoPagoCHlineEdit->setEnabled(false);
            ui->MensualidadCHlineEdit->setEnabled(false);
            ui->TotalCHlineEdit->setEnabled(false);
            ui->TasaInteresCHlineEdit->setEnabled(false);
            ui->MontoPrimaCHlineEdit->setEnabled(false);
            ui->ValorInmuebleCHlineEdit->setEnabled(false);
            ui->AgregarCreditoHpushButton->setEnabled(false);
            ui->CancelarCreditopushButton->setEnabled(true);
            ui->ActivarCreditopushButton->setEnabled(true);
            ui->DesactivarCreditopushButton->setEnabled(true);
        }
       // conn.connClose();
     }
     else
    {
        QMessageBox::critical(this, "Error","No se cargaron los datos");
        // QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }

}

void MainWindow4::on_ActivarCreditopushButton_clicked()
{
    QString id_credito;
    id_credito=ui->IDcreditoHipotecariolineEdit->text();
    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("update credito_hipotecario set activo = '1' where id_credito = '"+id_credito+"'");
    if(qry.exec())
    {
        QMessageBox::information(this,tr("Activada"),tr("El Credito Hipotecario del cliente a sido activado "));
        on_BuscarHipotecasCuentaPushButton_clicked();
        ui->IDcreditoHipotecariolineEdit->clear();
        ui->PeriodoPagoCHlineEdit->clear();
        ui->MensualidadCHlineEdit->clear();
        ui->TotalCHlineEdit->clear();
        ui->TasaInteresCHlineEdit->clear();
        ui->MontoPrimaCHlineEdit->clear();
        ui->ValorInmuebleCHlineEdit->clear();

        ui->IDcreditoHipotecariolineEdit->setEnabled(true);
        ui->PeriodoPagoCHlineEdit->setEnabled(true);
        ui->MensualidadCHlineEdit->setEnabled(true);
        ui->TotalCHlineEdit->setEnabled(true);
        ui->TasaInteresCHlineEdit->setEnabled(true);
        ui->MontoPrimaCHlineEdit->setEnabled(true);
        ui->ValorInmuebleCHlineEdit->setEnabled(true);
        ui->AgregarCreditoHpushButton->setEnabled(true);
        ui->CancelarCreditopushButton->setEnabled(true);
        ui->ActivarCreditopushButton->setEnabled(false);
        ui->DesactivarCreditopushButton->setEnabled(false);


      //  conn.connClose();
     }
     else
        QMessageBox::critical(this, "Error","No se pudo dar de alta");
}

void MainWindow4::on_DesactivarCreditopushButton_clicked()
{
    QString id_credito;
    id_credito=ui->IDcreditoHipotecariolineEdit->text();
    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("update credito_hipotecario set activo = '0' where id_credito = '"+id_credito+"'");
    if(qry.exec())
    {
        QMessageBox::information(this,tr("Activada"),tr("El Credito Hipotecario del cliente a sido desactivado "));
        on_BuscarHipotecasCuentaPushButton_clicked();
        ui->IDcreditoHipotecariolineEdit->clear();
        ui->PeriodoPagoCHlineEdit->clear();
        ui->MensualidadCHlineEdit->clear();
        ui->TotalCHlineEdit->clear();
        ui->TasaInteresCHlineEdit->clear();
        ui->MontoPrimaCHlineEdit->clear();
        ui->ValorInmuebleCHlineEdit->clear();

        ui->IDcreditoHipotecariolineEdit->setEnabled(true);
        ui->PeriodoPagoCHlineEdit->setEnabled(true);
        ui->MensualidadCHlineEdit->setEnabled(true);
        ui->TotalCHlineEdit->setEnabled(true);
        ui->TasaInteresCHlineEdit->setEnabled(true);
        ui->MontoPrimaCHlineEdit->setEnabled(true);
        ui->ValorInmuebleCHlineEdit->setEnabled(true);
        ui->AgregarCreditoHpushButton->setEnabled(true);
        ui->CancelarCreditopushButton->setEnabled(true);
        ui->ActivarCreditopushButton->setEnabled(false);
        ui->DesactivarCreditopushButton->setEnabled(false);


      //  conn.connClose();
     }
     else
        QMessageBox::critical(this, "Error","No se pudo dar de baja");
}

void MainWindow4::on_CancelarCreditopushButton_clicked()
{
    ui->IDcreditoHipotecariolineEdit->clear();
    ui->PeriodoPagoCHlineEdit->clear();
    ui->MensualidadCHlineEdit->clear();
    ui->TotalCHlineEdit->clear();
    ui->TasaInteresCHlineEdit->clear();
    ui->MontoPrimaCHlineEdit->clear();
    ui->ValorInmuebleCHlineEdit->clear();
    ui->BuscarHipotecariosCuentalineEdit->clear();

    ui->IDcreditoHipotecariolineEdit->setEnabled(false);
    ui->PeriodoPagoCHlineEdit->setEnabled(false);
    ui->MensualidadCHlineEdit->setEnabled(false);
    ui->TotalCHlineEdit->setEnabled(false);
    ui->TasaInteresCHlineEdit->setEnabled(false);
    ui->MontoPrimaCHlineEdit->setEnabled(false);
    ui->ValorInmuebleCHlineEdit->setEnabled(false);
    ui->AgregarCreditoHpushButton->setEnabled(false);
    ui->CancelarCreditopushButton->setEnabled(false);
    ui->ActivarCreditopushButton->setEnabled(false);
    ui->DesactivarCreditopushButton->setEnabled(false);
    conn.connClose();

}

void MainWindow4::on_AyudaClientespushButton_clicked()
{
    QMessageBox::information(this,tr("Ayuda"),tr("Esta es la ventana de registro de los datos de los clientes\n"
                                                 "1)Para registrar un cliente:\n"
                                                 "*Tienes que verificar que los campos esten llenos\n"
                                                 "*Que no exedan el numero de caracteres validos\n"
                                                 "*El ID cliente no se repita\n"
                                                 "*El ID de la sucursal exista\n"
                                                 "2)Formato de llenado correcto:\n"
                                                 "*Nombre: Diaz Munoz Victor Otniel\n"
                                                 "*Curp: DIMV960706HJCZXC00\n"
                                                 "*Fecha de Nacimiento: 1996-06-07\n"
                                                 "*Ciudad: Guadalajara"
                                                 "*Domicilio: Alberto Cinta #388"
                                                 "*Sexo: H\n"
                                                 "*Correo: vodem1010@gmailcom\n"
                                                 "*Telefono: 3311526834\n"
                                                 "*ID cliente: 1 ( verificar que este sin repetir)\n"
                                                 "*ID sucursal: 2 ( verificar que exista)\n"
                                                 "*Presiona Registrar Cliente para guardar los datos, este se ingresara por defecto como inactivo (0)\n"
                                                 "*Presiona Cancelar para borrar los datos escritos en los campos\n"
                                                 ));
}

void MainWindow4::on_AyudaClientesModipushButton_clicked()
{
    QMessageBox::information(this,tr("Ayuda"),tr("Esta es la ventana de Activaciones/Desactivaciones/modificaciones/eliminaciones de los datos de los clientes\n"
                                                 "1)Para modificar un cliente:\n"
                                                 "*Ingresa el ID del cliente para su busqueda\n"
                                                 "*En caso de que exista se habilitaran los campos , de lo contario seguiran bloquedaos, VERIFICA que este escrito correctamente el ID\n"
                                                 "*2)Para Activar y Desactivar un cliente:\n"
                                                 "Para poder adquirir cuentas y servicios:\n"
                                                 "*Selecciona Activar Cliente para dar de alta(bool 1)\n"
                                                 "*Selecciona Desactivar Cliente para dar de baja(bool 0)\n"
                                                 "*Al darlo de baja se elimina de manera logica, no permanente por lo que sus datos estaran en el sistema\n"
                                                 "*Dar de baja conlleva un efecto cascada por lo que si cuenta con cuentas y/o servicios estos pasaran de activos a inactivos"


                                                 ));
}

void MainWindow4::on_AyudaCuentaspushButton_clicked()
{
    QMessageBox::information(this,tr("Ayuda"),tr("Esta es la ventana de creacion de cuentas, para Activarlas y Desactivalas, asi como consultar cuantas cuentas tiene un cliente\n"
                                                 "1)Para registrar una cuenta:\n"
                                                 "*Se tiene que verificar que el cliente este activo, si solo esta en el sistema inactivo no puede tener cuentas  \n"
                                                 "*Si el cliente esta activo se busca el ID del mismo para habilitar los campos, si no se encuentra verfique que este sea el correcto y exista, ademas de estar activo\n"
                                                 "*El numero de cuenta se genera por si solo, para esto presione el boton generar, para asignarle un num de cuenta\n"
                                                 "*El codigo de seguridad se genera solo, para esto presione generar, para asignarle un codigo de seguridad a la cuenta\n"
                                                 "*Para Agregar los datos al sistema seleccione Agregar Cuenta, este se ingresara a la BD como inactiva (0) por default\n"
                                                 "*Seleccione Cancelar para borrar los datos de los campos e inhabilitar los campos\n"
                                                 "2)Para Activar o Desactivar una Cuenta:\n"
                                                 "*Presione de la tabla el CAMPO de la COLUMNA num_cuenta que quiere activar o desactivar, este se cargara a los campos y se inhabilitaran para seguridad\n"
                                                 "*Seleccione Activar Cuenta para activarla (bool 1)\n"
                                                 "*Seleccione Desactivar Cuenta para desactivarla (bool 0), al desactivarse la Cuenta se desactivan los servicios de este, ya sen seguros,inversiones, etc\n"
                                                 "*Formato correcto para Agregar una Cuenta:\n"
                                                 "*Numero de Cuenta: 234156890123456 (Presione generar)\n"
                                                 "*Saldo: 30000\n"
                                                 "*Fecha de Tramite: 2018-06-07\n"
                                                 "*Tipo: Premium\n"
                                                 "*Codigo de seguridad:123456\n"

                                                 ));
}

void MainWindow4::on_AyudaCitapushButton_clicked()
{
    QMessageBox::information(this,tr("Ayuda"),tr("Esta es la ventana de consulta de Citas\n"
                                                 "1)Para consultar una cita:\n"
                                                 "*Ingrese el ID de la cita del cliente  \n"
                                                 "*Si la cita esta registrada se mostraran los datos de la cita, sucursal y cliente, si no se muestra verfique que lo ingreso correctamente\n"
                                                 ));
}

void MainWindow4::on_AyudaSeguropushButton_clicked()
{
    QMessageBox::information(this,tr("Ayuda"),tr("Esta es la ventana de Contratacion de seguros, para Activarlos y Desactivalos, asi como consultar cuantos seguros tiene un cliente en una cuenta\n"
                                                 "1)Para registrar una cuenta:\n"
                                                 "*Se tiene que verificar que la cuenta del cliente este activa, si solo esta en el sistema inactiva no puede tener seguros  \n"
                                                 "*Si la cuenta del cliente esta activa se busca el ID de la misma para habilitar los campos, si no se encuentra verfique que este sea el correcto y exista, ademas de estar activa\n"
                                                 "*El numero de poliza es el ID del seguro, al ingresar verifique que este no se repita\n"
                                                 "*Para Agregar los datos al sistema seleccione Agregar Seguro, este se ingresara a la BD como inactivo (0) por default\n"
                                                 "*Seleccione Cancelar para borrar los datos de los campos e inhabilitar los campos\n"
                                                 "2)Para Activar o Desactivar un Seguro:\n"
                                                 "*Presione de la tabla el CAMPO de la COLUMNA num_poliza que quiere activar o desactivar, este se cargara a los campos y se inhabilitaran para seguridad\n"
                                                 "*Seleccione Activar Seguro para activarlo (bool 1)\n"
                                                 "*Seleccione Desactivar Seguro para desactivarlo (bool 0)\n"
                                                 "*Formato correcto para Agregar un Seguro:\n"
                                                 "*Numero de Poliza: 012345689 \n"
                                                 "*Empresa: Company S.A de C.V\n"
                                                 "*Descuento: Mensual (Tipo de Descuento del Seguro)\n"
                                                 "*Moneda: Pesos (Tipo de Moneda)\n"
                                                 "*Importe Prima Anual: 1000.00 (Costo Anual del Seguro)\n"
                                                 "*Cobertura: Company S.A de C.V (Empresa que cubre el Seguro)\n"
                                                 "*Suma asegurada: 100 000.00 (Monto Total del Seguro)\n"
                                                 "*Plazo de seguro: 20 (anios)\n"
                                                 "*Plazo de pago: 20 (anios)\n"
                                                 ));
}

void MainWindow4::on_AyudaCreditoHpushButton_clicked()
{
    QMessageBox::information(this,tr("Ayuda"),tr("Esta es la ventana de Credito Hipotecario, para Activarlos y Desactivalos, asi como consultar cuantos Creditos Hipotecarios tiene un cliente en una cuenta\n"
                                                 "1)Para registrar una Credito Hipotecario:\n"
                                                 "*Se tiene que verificar que la cuenta del cliente este activa, si solo esta en el sistema inactiva no puede tener seguros  \n"
                                                 "*Si la cuenta del cliente esta activa se busca el ID de la misma para habilitar los campos, si no se encuentra verfique que este sea el correcto y exista, ademas de estar activa\n"
                                                 "*El ID del credito H. al ingresar verifique que este no se repita\n"
                                                 "*Para Agregar los datos al sistema seleccione Agregar Credito H., este se ingresara a la BD como inactivo (0) por default\n"
                                                 "*Seleccione Cancelar para borrar los datos de los campos e inhabilitar los campos\n"
                                                 "2)Para Activar o Desactivar un Credito H.:\n"
                                                 "*Presione de la tabla el CAMPO de la COLUMNA Id_credito que quiere activar o desactivar, este se cargara a los campos y se inhabilitaran para seguridad\n"
                                                 "*Seleccione Activar Credito H. para activarlo (bool 1)\n"
                                                 "*Seleccione Desactivar Credito H. para desactivarlo (bool 0)\n"
                                                 "*Formato correcto para Agregar un Credito Hipotecario:\n"
                                                 "*ID del credito Hipotecario: 012345689 \n"
                                                 "*Periodo de Pago: 20 (anios) (Numero de anios en el que se saldara el pago del prestamo)\n"
                                                 "*Mensualidad: 2190.50 (Cantidad que se paga al mes)\n"
                                                 "*Valor Inmueble: 2 800 000 (Valor del inmueble asegurado)\n"
                                                 "*Tasa de Interes: 3.5 (Interes que se cobrara al Cliente)\n"
                                                 "*Monto Prima: 20000.00 (Monto que se cobrara de Interes)\n"
                                                 "*Total: 3 000 000.00 (Cantidad Total a Pagar)\n"
                                                 ));
}

void MainWindow4::on_AyudaPrestamospushButton_clicked()
{
    QMessageBox::information(this,tr("Ayuda"),tr("Esta es la ventana de Contratacion de Prestamos, para Activarlos y Desactivalos, asi como consultar cuantos Prestamos tiene un cliente en una cuenta\n"
                                                 "1)Para registrar una Prestamo:\n"
                                                 "*Se tiene que verificar que la cuenta del cliente este activa, si solo esta en el sistema inactiva no puede tener seguros  \n"
                                                 "*Si la cuenta del cliente esta activa se busca el ID de la misma para habilitar los campos, si no se encuentra verfique que este sea el correcto y exista, ademas de estar activa\n"
                                                 "*El ID del Prestamo al ingresar verifique que este no se repita\n"
                                                 "*Para Agregar los datos al sistema seleccione Agregar Prestamo, este se ingresara a la BD como inactivo (0) por default\n"
                                                 "*Seleccione Cancelar para borrar los datos de los campos e inhabilitar los campos\n"
                                                 "2)Para Activar o Desactivar un Prestamo:\n"
                                                 "*Presione de la tabla el CAMPO de la COLUMNA Id_prestamo que quiere activar o desactivar, este se cargara a los campos y se inhabilitaran para seguridad\n"
                                                 "*Seleccione Activar Prestamo para activarlo (bool 1)\n"
                                                 "*Seleccione Desactivar Prestamo para desactivarlo (bool 0)\n"
                                                 "*Formato correcto para Agregar un Prestamo:\n"
                                                 "*ID del Prestamo: 012345689 \n"
                                                 "*Tipo: Prestamo de Consumo (Tipo de Prestamo)\n"
                                                 "*Mensualidad: 300.00 (Cantidad que se paga al mes)\n"
                                                 "*Fecha de Aceptacion: 2018/03/27 (Fecha en que se acepto la solicitud)\n"
                                                 "*Periodo de Prestamo: 10 (meses) (Tiempo en el que se paga el prestamo en meses)\n"
                                                 "*Tasa de Interes: 3.2 (Interes que se le cobrara al Cliente)\n"
                                                 "*Total: 3000.00 (Cantidad Total a Pagar)\n"
                                                 ));
}

void MainWindow4::on_AyudaInversionpushButton_clicked()
{
    QMessageBox::information(this,tr("Ayuda"),tr("Esta es la ventana de Inversiones, para Activarlos y Desactivalos, asi como consultar cuantos Prestamos tiene un cliente en una cuenta\n"
                                                 "1)Para registrar una Inversion:\n"
                                                 "*Se tiene que verificar que la cuenta del cliente este activa, si solo esta en el sistema inactiva no puede tener seguros  \n"
                                                 "*Si la cuenta del cliente esta activa se busca el ID de la misma para habilitar los campos, si no se encuentra verfique que este sea el correcto y exista, ademas de estar activa\n"
                                                 "*El ID de la Inversion al ingresar verifique que este no se repita\n"
                                                 "*Para Agregar los datos al sistema seleccione Agregar Inversion, este se ingresara a la BD como inactivo (0) por default\n"
                                                 "*Seleccione Cancelar para borrar los datos de los campos e inhabilitar los campos\n"
                                                 "2)Para Activar o Desactivar una Inversion:\n"
                                                 "*Presione de la tabla el CAMPO de la COLUMNA Id_inversion que quiere activar o desactivar, este se cargara a los campos y se inhabilitaran para seguridad\n"
                                                 "*Seleccione Activar Inversion para activarlo (bool 1)\n"
                                                 "*Seleccione Desactivar Inversion para desactivarlo (bool 0)\n"
                                                 "*Formato correcto para Agregar una Inversion:\n"
                                                 "*ID de la Inversion: 012345689 \n"
                                                 "*Tipo: Bonos (Tipo de Inversion)\n"
                                                 "*Cantidad Invertida: 30 000 (Cantidad invertida por el Cliente)\n"
                                                 "*Tasa de Interes: 3.0 (Tasa de Interes de la Inversion)\n"
                                                 "*Tipo de Tasa: Activa (Tipo de Tasa Interes)\n"
                                                 "*Plazo: 30 (dias) (Plazo en el que se realizara la inversion en dias)\n"
                                                 ));
}

void MainWindow4::on_pushButton_clicked()  //Boton generador de  id Clientes
{
    MainWindow x;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    ui->IdClientelineEdit->setText(x.RandmKey(qrand()%11+5));   //Genera una llave aleatoria de  5 a 20 caracteres alfanumericos
}

void MainWindow4::on_pushButton_2_clicked()
{
    MainWindow x;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    ui->IDcreditoHipotecariolineEdit->setText(x.RandmKeyN(qrand()%16+5));  //Genera llave aleatoria de 5-20 char alfanumericos
}

void MainWindow4::on_pushButton_3_clicked()
{
    MainWindow x;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    ui->IDPrestamolineEdit->setText(x.RandmKeyN(qrand()%7+5));  //Genera llave aleatoria de 5-11 char alfanumericos
}

void MainWindow4::on_pushButton_4_clicked()
{
    MainWindow x;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    ui->IDInversionlineEdit->setText(x.RandmKeyN(qrand()%7+5));  //Genera llave aleatoria de 5-11 char alfanumericos
}

void MainWindow4::on_CancelarClientepushButton_clicked()
{
    //QMessageBox::information(this,tr("Error"),LocalActual);
}

void MainWindow4::on_CorreoClientelineEdit_textEdited(const QString &arg1)
{
    QPalette *palette = new QPalette();
    QPalette *palette2 = new QPalette();
    palette->setColor(QPalette::Text,Qt::red);
    palette2->setColor(QPalette::Text,Qt::black);
    if(mailREX.exactMatch(arg1))
    {
        ui->CorreoClientelineEdit->setPalette(*palette2);
    }
    else
    {
        ui->CorreoClientelineEdit->setPalette(*palette);
    }
}

void MainWindow4::on_TelefonoClientelineEdit_textEdited(const QString &arg1)
{
    QPalette *palette = new QPalette();
    QPalette *palette2 = new QPalette();
    palette->setColor(QPalette::Text,Qt::red);
    palette2->setColor(QPalette::Text,Qt::black);
    if(NumberREX.exactMatch(arg1))
    {
        ui->TelefonoClientelineEdit->setPalette(*palette2);
    }
    else
    {
        ui->TelefonoClientelineEdit->setPalette(*palette);
    }
}
