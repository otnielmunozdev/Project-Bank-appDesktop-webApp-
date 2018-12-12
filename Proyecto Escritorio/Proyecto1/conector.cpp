#include "conector.h"
#include <QtSql>
#include <QString>
#include <QSqlDatabase>

void Conector::connClose()
{
    mydb.close(); //CERRAMOS LA BASE DE DATOS
    mydb.removeDatabase(QSqlDatabase::defaultConnection); //ACTUALIZA LA BASE DE DATOS
}
bool Conector::connOpen() // Info del servidor desk
{
    mydb = mydb.database("BDDesk");
    mydb.setHostName("192.168.1.5");
    mydb.setDatabaseName("Banco");
    mydb.setPort(3306);
    mydb.setPassword("AdmonBasesDatos");
    mydb.setUserName("Lalo");
    if(mydb.open())
    {
        qDebug()<< ("Server Desk no conectado........");
        return false;
     }
    else{
        qDebug()<<("Conectada a la Base de Datos ......");
        return true;
    }
}
bool Conector::connOpenWeb() // Infor de servidor Web
{
    mydb = mydb.database("BDWeb"); // Conector de base MySql
    mydb.setHostName("192.168.1.4");
    mydb.setDatabaseName("bancoRataWeb");
    mydb.setPort(3306);
    mydb.setPassword("AdmonBaseDatos");
    mydb.setUserName("diego");

    if(!mydb.open())
    {
        qDebug()<< ("Server Web no conectado........");
        return false;
     }
    else{
        qDebug()<<("Conectada a la Base de Datos Web......");
        return true;
    }
}

