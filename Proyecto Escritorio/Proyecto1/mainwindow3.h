#ifndef MAINWINDOW3_H
#define MAINWINDOW3_H
#include <QRegExp>

#include <QMainWindow>
namespace Ui {
class MainWindow3;
}

class MainWindow3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow3(QWidget *parent = 0);
    QString LocalActual,PuestoUsuario,NombreUsuario,CodigoUsuario;
    int Conta=0;
    QRegExp mailREX,NameREX,NumberREX;
    ~MainWindow3();

private slots:
    void on_Salir2pushButton_clicked();

    void on_Salir3pushButton_clicked();

    void on_AgregarpushButton_clicked();

    void on_IdSucursalcomboBox_currentIndexChanged(const QString &arg1);

    void on_BuscarPushButton_clicked();

    void on_ModificarpushButton_clicked();

    void on_CancelarBpushButton_clicked();

    void on_BuscarlineEdit_textChanged(const QString &arg1);

    void on_EliminarpushButton_clicked();

    void on_AyudapushButton_clicked();

    void on_AyudaModipushButton_clicked();

    void on_pushButton_clicked();

    void on_CorreolineEdit_textEdited(const QString &arg1);

    void on_TelefonolineEdit_textEdited(const QString &arg1);

    void on_NombrelineEdit_textEdited(const QString &arg1);

    void on_ModificarCorreolineEdit_textEdited(const QString &arg1);

    void on_ModificarTelefonolineEdit_textEdited(const QString &arg1);

private:
    Ui::MainWindow3 *ui;
};

#endif // MAINWINDOW3_H
