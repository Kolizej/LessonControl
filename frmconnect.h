#ifndef FRMCONNECT_H
#define FRMCONNECT_H

#include <QWidget>
#include <QtNetwork>

namespace Ui {
    class frmConnect;
}

class frmConnect : public QWidget
{
    Q_OBJECT

public:
    explicit frmConnect(QWidget *parent = 0);
    ~frmConnect();

private slots:
    void on_chbCreateServer_stateChanged(int arg1);
    void moveWindowToCenter();
    void on_btnOk_clicked();
    bool testConnection(QString server_adress, quint16 server_port);

private:
    Ui::frmConnect *ui;
    QTcpSocket test_connect;
};

#endif // FRMCONNECT_H
