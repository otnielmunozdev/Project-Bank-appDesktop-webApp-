#ifndef MAINWINDOW5_H
#define MAINWINDOW5_H

#include <QMainWindow>
#include <QtSql>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class MainWindow5;
}

class MainWindow5 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow5(QWidget *parent = 0);
    ~MainWindow5();

private slots:
    void on_Salir5pushButton_clicked();

private:
    Ui::MainWindow5 *ui;
    QSqlTableModel *mModel;
    QSqlDatabase *mDatabase;
};

#endif // MAINWINDOW5_H
