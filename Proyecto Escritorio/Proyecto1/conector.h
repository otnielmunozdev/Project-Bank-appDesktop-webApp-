#ifndef CONECTOR_H
#define CONECTOR_H
#include <QtSql>
#include <QString>
#include <QSqlDatabase>

class Conector
{
    public:
        QSqlDatabase mydb;
        void connClose();
        Conector()
        {
            mydb.addDatabase("QMYSQL", "BDDesk");
            mydb.addDatabase("QMYSQL", "BDWeb");
        }

        bool connOpenWeb();
        bool connOpen();//METODO PARA CERRAR LA BASE DE DATOS
};

#endif // CONECTOR_H
