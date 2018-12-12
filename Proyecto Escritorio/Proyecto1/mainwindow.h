#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mainwindow2.h>
#include <QtSql>
#include <QString>
#include <QTime>
#include <QGlobal.h>
#include "conector.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString HostEsc,HostWeb,DataEsc,DataWeb,PassEsc,PassWeb,UserEsc,UserWeb;
    MainWindow2 *ventana6;
    Conector conn;
    ~MainWindow();

    QString RandmKey(int y)
    {
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        QString llave;
        char x;
        for(int r=0; r<y; r++)
        {
                int w=qrand()%2;
                if(w==0)
                {
                    w=qrand()%9+48;
                }
                else
                {
                    w=qrand()%25+65;
                }
                x=w;
                llave=llave+x;
        }
        return llave;
    }
    QString RandmKeyN(int y)
    {
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        QString llave;
        char x;
        for(int r=0; r<y; r++)
        {
                int w=qrand()%9+48;
                x=w;
                llave=llave+x;
        }
        return llave;
    }
private slots:
    void on_LoginpushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
