#ifndef FRMCLIENT_H
#define FRMCLIENT_H

#include <QWidget>
#include <QtNetwork>
#include "ClientInformation.h"

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

private slots:
    void moveWindowToCenter();
    void sendMessage();
    void connectToServer(QString server_adress, quint16 server_port);
    QString makeMessageString();
};

#endif // FRMCLIENT_H
