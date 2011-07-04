#ifndef FRMCLIENT_H
#define FRMCLIENT_H

#include <QWidget>
#include <QtNetwork>
#include "ClientInformation.h"
#include "QMessageBox"

namespace Ui {
    class frmClient;
}

class frmClient : public QWidget
{
    Q_OBJECT

public:
    explicit frmClient(QWidget *parent = 0);
    ~frmClient();

private:
    Ui::frmClient *ui;
    QTcpSocket client;
    char* str_message;
    ClientInfo cInfo;
    QMessageBox msg;

private slots:
    void moveWindowToCenter();
    void sendMessage(QString status);
    void connectToServer(QString server_adress, quint16 server_port);
    void sendCloseMessage();
    QString makeMessageString();
    void on_btnDisconnect_clicked();
};

#endif // FRMCLIENT_H
