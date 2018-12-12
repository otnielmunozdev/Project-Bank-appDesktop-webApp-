#include "mainwindow3.h"
#include "ui_mainwindow3.h"
#include "mainwindow2.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QDate>
#include <QRegExp>
#include <QPalette>
#include "conector.h"

MainWindow3::MainWindow3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow3)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->IdlineEdit->setEnabled(false);
    mailREX.setPattern("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    NumberREX.setPattern("\\w{8,10}");
    NumberREX.setCaseSensitivity(Qt::CaseInsensitive);
    NumberREX.setPatternSyntax(QRegExp::RegExp);
}

MainWindow3::~MainWindow3()
{
    delete ui;
}

void MainWindow3::on_Salir2pushButton_clicked()
{
   // MainWindow2 *ventana4 = new MainWindow2();
    //ventana4->setVisible(true);
    this->setVisible(false);
    Conta=0;
}

void MainWindow3::on_Salir3pushButton_clicked()
{
   // MainWindow2 *ventana5 = new MainWindow2();
    //ventana5->setVisible(true);
    this->setVisible(false);
    Conta=0;
}

void MainWindow3::on_AgregarpushButton_clicked()
{
    Conector conn;
    QString id_empleado, nombre, curp, puesto,sexo,correo_electronico , telefono,fecha_nac,rfc, salario,horario,id_suc;
    id_empleado=ui->IdlineEdit->text();
    nombre = ui->NombrelineEdit->text();
    curp = ui->CURPlineEdit->text();
    puesto = ui->PuestolineEdit->text();
    sexo = ui->Sexo2comboBox->currentText();
    //sexo = ui->MujerradioButton->checkStateSet();
    //sexo2 = ui->HombreradioButton->text();
    correo_electronico = ui->CorreolineEdit->text();
    telefono = ui->TelefonolineEdit->text();
    fecha_nac = ui->FechaNacdateEdit->text();
    rfc = ui->RFClineEdit->text();
    salario = ui->SalariolineEdit->text();
    horario = ui->HorariotimeEdit->text();
    id_suc = ui->ID_suclineEdit->text();

    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("insert into empleado (id_empleado, nombre, curp , puesto, sexo, correo_electronico,telefono,fecha_nac,rfc,salario,horario,id_suc ) values ('"+id_empleado+"','"+nombre+"', '"+curp+"','"+puesto+"','"+sexo+"', '"+correo_electronico+"', '"+telefono+"', '"+fecha_nac+"', '"+rfc+"', '"+salario+"', '"+horario+"', '"+id_suc+"')");

    if(qry.exec())
    {
        QMessageBox::information(this,tr("Guardando"),tr("     Los datos se agregaron a la Base de Datos     "));
        ui->IdlineEdit->clear();
        ui->NombrelineEdit->clear();
        ui->CURPlineEdit->clear();
        ui->PuestolineEdit->clear();
        ui->CorreolineEdit->clear();
        ui->TelefonolineEdit->clear();
        ui->FechaNacdateEdit->clearMaximumDate();
        ui->RFClineEdit->clear();
        ui->SalariolineEdit->clear();
        ui->HorariotimeEdit->clear();
        ui->ID_suclineEdit->clear();

        conn.connClose();
     }
     else

            QMessageBox::critical(this, "Error","Llena el formulario correctamente\n*Si el error continua verifica la ayuda en la parte izquierda de la ventana");
            //QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void MainWindow3::on_IdSucursalcomboBox_currentIndexChanged(const QString &arg1)
{

}

void MainWindow3::on_BuscarPushButton_clicked()
{
    Conector conn;
    QString buscar=ui->BuscarlineEdit->text();
    if(buscar==CodigoUsuario)
    {
        QMessageBox::critical(this, "Error","No está permitido realizar modificación sobre tu información propia.");
        return;
    }
    QDate date = QDate::currentDate();
    QString dateString = date.toString();
    conn.connOpen();
    QSqlQuery  qry(conn.mydb);

    qry.prepare("SELECT * from empleado WHERE  id_empleado = '"+buscar+"'");
    if(qry.exec())
    {

        while(qry.next())
        {
            QMessageBox::information(this,tr("Cargando"),tr("Los campos se han activado ahora se pueden Modificar o Eliminar"));
            ui->ModificarIdlineEdit->setText(qry.value(0).toString());
            ui->ModificarNombrelineEdit->setText(qry.value(1).toString());
            ui->ModificarCURPlineEdit->setText(qry.value(2).toString());
            ui->ModificarPuestolineEdit->setText(qry.value(3).toString());
            ui->SexoModificarcomboBox->setCurrentText(qry.value(4).toString());
            ui->ModificarCorreolineEdit->setText(qry.value(5).toString());
            ui->ModificarTelefonolineEdit->setText(qry.value(6).toString());
            ui->ModificarFechaNacdateEdit->setDate(qry.value(7).toDate());
            ui->ModificarRFClineEdit->setText(qry.value(8).toString());
            ui->ModificarSalariolineEdit->setText(qry.value(9).toString());
            ui->ModificarHorariotimeEdit->setTime(qry.value(10).toTime());
            ui->ID_sucModificarlineEdit->setText(qry.value(11).toString());

            //ui->ModificarIdlineEdit->setEnabled(true);
            ui->ModificarNombrelineEdit->setEnabled(true);
            ui->ModificarCURPlineEdit->setEnabled(true);
            ui->ModificarPuestolineEdit->setEnabled(true);
            ui->SexoModificarcomboBox->setEnabled(true);
            ui->ModificarCorreolineEdit->setEnabled(true);
            ui->ModificarTelefonolineEdit->setEnabled(true);
            ui->ModificarFechaNacdateEdit->setEnabled(true);
            ui->ModificarRFClineEdit->setEnabled(true);
            ui->ModificarSalariolineEdit->setEnabled(true);
            ui->ModificarHorariotimeEdit->setEnabled(true);
            ui->ID_sucModificarlineEdit->setEnabled(true);
            ui->EliminarpushButton->setEnabled(true);
            ui->ModificarpushButton->setEnabled(true);
            ui->CancelarBpushButton->setEnabled(true);
        }
        conn.connClose();
     }
     else
    {
        QMessageBox::critical(this, "Error","Llena el formulario correctamente\n*Si el error continua verifica la ayuda en la parte izquierda de la ventana");
        //QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}

void MainWindow3::on_ModificarpushButton_clicked()
{
    Conector conn;
    QString  id_empleado, nombre, curp, puesto,sexo,correo_electronico , telefono,fecha_nac,rfc, salario,horario,id_suc;
    id_empleado=ui->ModificarIdlineEdit->text();
    nombre = ui->ModificarNombrelineEdit->text();
    curp = ui->ModificarCURPlineEdit->text();
    puesto = ui->ModificarPuestolineEdit->text();
    sexo = ui->SexoModificarcomboBox->currentText();
    correo_electronico = ui->ModificarCorreolineEdit->text();
    telefono = ui->ModificarTelefonolineEdit->text();
    fecha_nac = ui->ModificarFechaNacdateEdit->text();
    rfc = ui->ModificarRFClineEdit->text();
    salario = ui->ModificarSalariolineEdit->text();
    horario = ui->ModificarHorariotimeEdit->text();
    id_suc = ui->ID_sucModificarlineEdit->text();
    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("update empleado set nombre = '"+nombre+"', curp = '"+curp+"' , puesto = '"+puesto+"', sexo = '"+sexo+"', correo_electronico = '"+correo_electronico+"',telefono =  '"+telefono+"',fecha_nac = '"+fecha_nac+"',rfc = '"+rfc+"',salario =  '"+salario+"',horario =  '"+horario+"',id_suc = '"+id_suc+"' where id_empleado = '"+id_empleado+"'");

    if(qry.exec())
    {
        QMessageBox::information(this,tr("Modificación"),tr("Los datos del empleado se han modificado correctamente"));
        ui->ModificarIdlineEdit->clear();
        ui->ModificarNombrelineEdit->clear();
        ui->ModificarCURPlineEdit->clear();
        ui->ModificarPuestolineEdit->clear();
        ui->SexoModificarcomboBox->clearEditText();
        ui->ModificarCorreolineEdit->clear();
        ui->ModificarTelefonolineEdit->clear();
        ui->ModificarFechaNacdateEdit->clearMaximumDate();
        ui->ModificarRFClineEdit->clear();
        ui->ModificarSalariolineEdit->clear();
        ui->ModificarHorariotimeEdit->clear();
        ui->ID_sucModificarlineEdit->clear();
        ui->BuscarlineEdit->clear();

        ui->ModificarIdlineEdit->setEnabled(false);
        ui->ModificarNombrelineEdit->setEnabled(false);
        ui->ModificarCURPlineEdit->setEnabled(false);
        ui->ModificarPuestolineEdit->setEnabled(false);
        ui->SexoModificarcomboBox->setEnabled(false);
        ui->ModificarCorreolineEdit->setEnabled(false);
        ui->ModificarTelefonolineEdit->setEnabled(false);
        ui->ModificarFechaNacdateEdit->setEnabled(false);
        ui->ModificarRFClineEdit->setEnabled(false);
        ui->ModificarSalariolineEdit->setEnabled(false);
        ui->ModificarHorariotimeEdit->setEnabled(false);
        ui->ID_sucModificarlineEdit->setEnabled(false);
        ui->EliminarpushButton->setEnabled(false);
        ui->ModificarpushButton->setEnabled(false);
        ui->CancelarBpushButton->setEnabled(false);
        conn.connClose();
     }
     else
        QMessageBox::critical(this, "Error","Llena el formulario correctamente\n*Si el error continua verifica la ayuda en la parte izquierda de la ventana");
         //QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void MainWindow3::on_CancelarBpushButton_clicked()
{
    ui->ModificarIdlineEdit->clear();
    ui->ModificarNombrelineEdit->clear();
    ui->ModificarCURPlineEdit->clear();
    ui->ModificarPuestolineEdit->clear();
    ui->SexoModificarcomboBox->clearEditText();
    ui->ModificarCorreolineEdit->clear();
    ui->ModificarTelefonolineEdit->clear();
    ui->ModificarFechaNacdateEdit->clearMaximumDate();
    ui->ModificarRFClineEdit->clear();
    ui->ModificarSalariolineEdit->clear();
    ui->ModificarHorariotimeEdit->clear();
    ui->ID_sucModificarlineEdit->clear();
    ui->BuscarlineEdit->clear();
    ui->ModificarIdlineEdit->setEnabled(false);
    ui->ModificarNombrelineEdit->setEnabled(false);
    ui->ModificarCURPlineEdit->setEnabled(false);
    ui->ModificarPuestolineEdit->setEnabled(false);
    ui->SexoModificarcomboBox->setEnabled(false);
    ui->ModificarCorreolineEdit->setEnabled(false);
    ui->ModificarTelefonolineEdit->setEnabled(false);
    ui->ModificarFechaNacdateEdit->setEnabled(false);
    ui->ModificarRFClineEdit->setEnabled(false);
    ui->ModificarSalariolineEdit->setEnabled(false);
    ui->ModificarHorariotimeEdit->setEnabled(false);
    ui->ID_sucModificarlineEdit->setEnabled(false);
    ui->EliminarpushButton->setEnabled(false);
    ui->ModificarpushButton->setEnabled(false);
    ui->CancelarBpushButton->setEnabled(false);
}

void MainWindow3::on_BuscarlineEdit_textChanged(const QString &arg1)
{

}

void MainWindow3::on_EliminarpushButton_clicked()
{
    Conector conn;
    QString  id_empleado, nombre, curp, puesto,sexo,correo_electronico , telefono,fecha_nac,rfc, salario,horario,id_suc;
    id_empleado=ui->ModificarIdlineEdit->text();
    nombre = ui->ModificarNombrelineEdit->text();
    curp = ui->ModificarCURPlineEdit->text();
    puesto = ui->ModificarPuestolineEdit->text();
    sexo = ui->SexoModificarcomboBox->currentText();
    correo_electronico = ui->ModificarCorreolineEdit->text();
    telefono = ui->ModificarTelefonolineEdit->text();
    fecha_nac = ui->ModificarFechaNacdateEdit->text();
    rfc = ui->ModificarRFClineEdit->text();
    salario = ui->ModificarSalariolineEdit->text();
    horario = ui->ModificarHorariotimeEdit->text();
    id_suc = ui->ID_sucModificarlineEdit->text();
    conn.connOpen();
    QSqlQuery qry(conn.mydb);
    qry.prepare("Delete from empleado where id_empleado = '"+id_empleado+"'" );

    if(qry.exec())
    {
        QMessageBox::information(this,tr("Eliminación"),tr("Los datos del empleado se han eliminado correctamente"));
        ui->ModificarIdlineEdit->clear();
        ui->ModificarNombrelineEdit->clear();
        ui->ModificarCURPlineEdit->clear();
        ui->ModificarPuestolineEdit->clear();
        ui->SexoModificarcomboBox->clearEditText();
        ui->ModificarCorreolineEdit->clear();
        ui->ModificarTelefonolineEdit->clear();
        ui->ModificarFechaNacdateEdit->clearMaximumDate();
        ui->ModificarRFClineEdit->clear();
        ui->ModificarSalariolineEdit->clear();
        ui->ModificarHorariotimeEdit->clear();
        ui->ID_sucModificarlineEdit->clear();
        ui->BuscarlineEdit->clear();

        ui->ModificarIdlineEdit->setEnabled(false);
        ui->ModificarNombrelineEdit->setEnabled(false);
        ui->ModificarCURPlineEdit->setEnabled(false);
        ui->ModificarPuestolineEdit->setEnabled(false);
        ui->SexoModificarcomboBox->setEnabled(false);
        ui->ModificarCorreolineEdit->setEnabled(false);
        ui->ModificarTelefonolineEdit->setEnabled(false);
        ui->ModificarFechaNacdateEdit->setEnabled(false);
        ui->ModificarRFClineEdit->setEnabled(false);
        ui->ModificarSalariolineEdit->setEnabled(false);
        ui->ModificarHorariotimeEdit->setEnabled(false);
        ui->ID_sucModificarlineEdit->setEnabled(false);
        ui->EliminarpushButton->setEnabled(false);
        ui->ModificarpushButton->setEnabled(false);
        ui->CancelarBpushButton->setEnabled(false);
        conn.connClose();
     }
     else
        QMessageBox::critical(this, "Error","Hubo una falla al eliminar\n*Si el error continua verifica la ayuda en la parte izquierda de la ventana");
        //QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void MainWindow3::on_AyudapushButton_clicked()
{
    QMessageBox::information(this,tr("Ayuda"),tr("Esta es la ventana de registro de los datos de los empleados\n"
                                                 "1)Para registrar un empleado:\n"
                                                 "*Tienes que verificar que los campos esten llenos\n"
                                                 "*Que no exedan el numero de caracteres validos\n"
                                                 "*El ID empleado no se repita\n"
                                                 "*El ID de la sucursal exista\n"
                                                 "2)Formato de llenado correcto:\n"
                                                 "*Nombre: Diaz Munoz Victor Otniel\n"
                                                 "*Curp: DIMV960706HJCZXC00\n"
                                                 "*Fecha de Nacimiento: 1996-06-07\n"
                                                 "*RFC: VIC9606\n"
                                                 "*Sexo: H\n"
                                                 "*Correo: vodem1010@gmailcom\n"
                                                 "*Telefono: 3311526834\n"
                                                 "*Puesto de Trabajo: Administrador\n"
                                                 "*Salario: 30000\n"
                                                 "*ID empleado: 1 ( verificar que este sin repetir)\n"
                                                 "*ID sucursal: 2 ( verificar que exista)\n"
                                                 "*Horario: 08:00\n"
                                                 "*Presiona Registrar Empleado para guardar los datos\n"
                                                 "*Presiona Cancelar para borrar los datos escritos en los campos\n"
                                                 ));
}

void MainWindow3::on_AyudaModipushButton_clicked()
{
    QMessageBox::information(this,tr("Ayuda"),tr("Esta es la ventana de modificaciones o eliminaciones de los datos de los empleados\n"
                                                 "1)Para modificar o eliminar un empleado:\n"
                                                 "*Verifica si el empleado existe ingresando su ID en el campo buscar\n"
                                                 "*En caso de existir se activaran los campos con sus datos, de lo contrario no se llevara a cabo ninguna accion, ni se activaran los campos\n"
                                                 "*Selecciona la opcion que quieres llevar a cabo\n"
                                                 "*El ID del empleado no se puede modificar\n"
                                                 "2)En caso de eliminar el empleado:\n"
                                                 "*Este se elimina de manera fisica de la BD, por lo cual se elimina permanentemente\n"
                                                 "*Selecciona Cancelar Busqueda para eliminar los datos ingresados\n"

                                                 ));
}

void MainWindow3::on_pushButton_clicked()
{
    MainWindow x;
    ui->IdlineEdit->setText(x.RandmKey(qrand()%25+5));
}


void MainWindow3::on_CorreolineEdit_textEdited(const QString &arg1)
{
    QPalette *palette = new QPalette();
    QPalette *palette2 = new QPalette();
    palette->setColor(QPalette::Text,Qt::red);
    palette2->setColor(QPalette::Text,Qt::black);
    if(mailREX.exactMatch(arg1))
    {
        ui->CorreolineEdit->setPalette(*palette2);
    }
    else
    {
        ui->CorreolineEdit->setPalette(*palette);
    }
}

void MainWindow3::on_TelefonolineEdit_textEdited(const QString &arg1)
{
    QPalette *palette = new QPalette();
    QPalette *palette2 = new QPalette();
    palette->setColor(QPalette::Text,Qt::red);
    palette2->setColor(QPalette::Text,Qt::black);
    if(NumberREX.exactMatch(arg1))
    {
        ui->TelefonolineEdit->setPalette(*palette2);
    }
    else
    {
        ui->TelefonolineEdit->setPalette(*palette);
    }
}

void MainWindow3::on_NombrelineEdit_textEdited(const QString &arg1)
{
   //Hacer manualmente este... quizá
}

void MainWindow3::on_ModificarCorreolineEdit_textEdited(const QString &arg1)
{
    QPalette *palette = new QPalette();
    QPalette *palette2 = new QPalette();
    palette->setColor(QPalette::Text,Qt::red);
    palette2->setColor(QPalette::Text,Qt::black);
    if(mailREX.exactMatch(arg1))
    {
        ui->ModificarCorreolineEdit->setPalette(*palette2);
    }
    else
    {
        ui->ModificarCorreolineEdit->setPalette(*palette);
    }
}

void MainWindow3::on_ModificarTelefonolineEdit_textEdited(const QString &arg1)
{
    QPalette *palette = new QPalette();
    QPalette *palette2 = new QPalette();
    palette->setColor(QPalette::Text,Qt::red);
    palette2->setColor(QPalette::Text,Qt::black);
    if(NumberREX.exactMatch(arg1))
    {
        ui->ModificarTelefonolineEdit->setPalette(*palette2);
    }
    else
    {
        ui->ModificarTelefonolineEdit->setPalette(*palette);
    }
}
