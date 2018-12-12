#ifndef MAINWINDOW4_H
#define MAINWINDOW4_H

#include <QMainWindow>
#include <QTime>
#include <QGlobal.h>
#include <QRegExp>
#include "conector.h"
#include "hfondo.h"

namespace Ui {
class MainWindow4;
}

class MainWindow4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow4(QWidget *parent = 0);
    QString LocalActual,PuestoUsuario,NombreUsuario,CodigoUsuario;
    QRegExp mailREX,NameREX,NumberREX;
    Conector conn;
    int Conta=0;
    ~MainWindow4();
    void lock();

private slots:
    void on_Salir12pushButton_clicked();

    void on_AgregarClientepushButton_clicked();

    void on_ModificarClientepushButton_clicked();

    void on_BuscarClientePushButton_2_clicked();

    void on_CancelarClientesBpushButton_clicked();

    void on_EliminarClientepushButton_clicked();

    void on_ActivarClientepushButton_clicked();

    void on_GenerarNumCuentapushButton_clicked();

    void on_GenerarCodigoSeguridadpushButton_clicked();

    void on_AgregarCuentapushButton_clicked();

    void on_BuscarClientePushButton_clicked();

    void on_CuentasTableview_activated(const QModelIndex &index);

    void on_CancelarCuentapushButton_clicked();

    void on_BuscarCitaClientePushButton_clicked();

    void on_ActivarCuentapushButton_clicked();

    void on_DesactivarCuentapushButton_clicked();

    void on_AgregarSegurospushButton_clicked();

    void on_BuscarCuentaSegurosPushButton_clicked();

    void on_ActivarseguropushButton_clicked();

    void on_SegurostableView_activated(const QModelIndex &index);

    void on_DesactivarseguropushButton_clicked();

    void on_CancelarSegurospushButton_clicked();

    void on_AgregarPrestamopushButton_clicked();

    void on_BuscarPrestamosCuentPushButton_clicked();

    void on_PrestamotableView_activated(const QModelIndex &index);

    void on_ActivarPrestamopushButton_clicked();

    void on_DesactivarPrestamopushButton_clicked();

    void on_CancelarPrestamopushButton_clicked();

    void on_AgregarInversionpushButton_clicked();

    void on_BuscarcuentaInversionPushButton_clicked();

    void on_InversiontableView_activated(const QModelIndex &index);

    void on_ActivarInversionpushButton_clicked();

    void on_DesactivarInversionpushButton_clicked();

    void on_CancelarInversionpushButton_clicked();

    void on_AgregarCreditoHpushButton_clicked();

    void on_BuscarHipotecasCuentaPushButton_clicked();

    void on_CreditoHipotecariotableView_activated(const QModelIndex &index);

    void on_ActivarCreditopushButton_clicked();

    void on_DesactivarCreditopushButton_clicked();

    void on_CancelarCreditopushButton_clicked();

    void on_AyudaClientespushButton_clicked();

    void on_AyudaClientesModipushButton_clicked();

    void on_AyudaCuentaspushButton_clicked();

    void on_AyudaCitapushButton_clicked();

    void on_AyudaSeguropushButton_clicked();

    void on_AyudaCreditoHpushButton_clicked();

    void on_AyudaPrestamospushButton_clicked();

    void on_AyudaInversionpushButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_CancelarClientepushButton_clicked();

    void on_CorreoClientelineEdit_textEdited(const QString &arg1);

    void on_TelefonoClientelineEdit_textEdited(const QString &arg1);

private:
    Ui::MainWindow4 *ui;
};

#endif // MAINWINDOW4_H
