#ifndef MAINWINDOW6_H
#define MAINWINDOW6_H

#include <QMainWindow>

namespace Ui {
class MainWindow6;
}

class MainWindow6 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow6(QWidget *parent = 0);
    QString LocalActual,PuestoUsuario,NombreUsuario;
    ~MainWindow6();

private slots:
    void on_Home2pushButton_clicked();

    void on_EmpleadoSalirpushButton_clicked();

    void on_ClientesEmpleadospushButton_clicked();

    void on_actionMostrar_triggered();

    void on_pushButton_clicked();

private:
    Ui::MainWindow6 *ui;
};

#endif // MAINWINDOW6_H
