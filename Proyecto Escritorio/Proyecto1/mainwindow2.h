#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include <mainwindow3.h>
#include <mainwindow4.h>
#include <mainwindow8.h>

namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = 0);
    QString LocalActual,PuestoUsuario,NombreUsuario,CodigoUsuario;
    MainWindow3 *ventana2=nullptr;
    MainWindow4 *ventana3=nullptr;
    MainWindow8 *ventana0=nullptr;
    bool Corre=false;
    bool _up=true,_down=false;
    int valor=0;
    ~MainWindow2();
    void Mover();
    void SetInfo();
    int Cantidad(QString DB,int b);

private slots:

    void on_HomepushButton_clicked();

    void on_EmpleadospushButton_clicked();

    void on_SalirpushButton_clicked();

    void on_ClientespushButton_clicked();

    void on_actionMostrar_triggered();

    void on_actionMostrar_2_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow2 *ui;
};

#endif // MAINWINDOW2_H
