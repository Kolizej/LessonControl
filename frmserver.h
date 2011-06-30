#ifndef FRMSERVER_H
#define FRMSERVER_H

#include <QWidget>
#include <QtNetwork/QtNetwork>
#include "QtNetwork/QTcpServer"
#include "QtNetwork/QTcpSocket"
#include "ClientInformation.h"

namespace Ui {
    class frmServer;
}

class frmServer : public QWidget
{
    Q_OBJECT

public:
    explicit frmServer(QWidget *parent = 0);
    ~frmServer();

private:
    Ui::frmServer *ui;
    QTcpServer server;
    QTcpSocket *client;
    ClientInfo ci;
    QList<ClientInfo> list_ci;

private slots:
    void moveWindowToCenter();
    void acceptConnection();
    void startRead();
    void parseMessage(QString message);
    void setParams();
};

#endif // FRMSERVER_H
