#ifndef MAINWINDOW8_H
#define MAINWINDOW8_H

#include <QMainWindow>
#include <QSqlTableModel>

namespace Ui {
class MainWindow8;
}

class MainWindow8 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow8(QWidget *parent = 0);
    int Conta=0;
    ~MainWindow8();

private slots:
    void on_Salir5pushButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow8 *ui;
    QSqlTableModel *mModel;
    QSqlDatabase *mDatabase;
};

#endif // MAINWINDOW8_H
