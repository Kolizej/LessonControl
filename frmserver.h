#ifndef FRMSERVER_H
#define FRMSERVER_H

#include <QWidget>
#include <QtNetwork/QtNetwork>
#include "QtNetwork/QTcpServer"
#include "QtNetwork/QTcpSocket"
#include "ClientInformation.h"
#include "QMessageBox"
#include "QListWidgetItem"

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
    QMessageBox msg;

protected:
    void closeEvent(QCloseEvent *ce);

private slots:
    void moveWindowToCenter();
    void acceptConnection();
    void startRead();
    void parseMessage(QString message);
    void setParams();
    bool isClientInfoExists(ClientInfo clInf);
    void setMainParams();
    void setDefaultParams();
    void setWorkstationParams(QString wsname);
    void on_listWorkstations_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
};

#endif // FRMSERVER_H
