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
    char* str_message;
    QTcpSocket client_server;

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
    void on_listWorkstations_currentRowChanged(int currentRow);
    void sendMessage(QString message_, QString host);
    void connectToServer(QString server_adress, quint16 server_port);
    void on_btnCall_clicked();
    void on_btnCallCancel_clicked();
    void setMainTempPictures(int value);
    void setMainVolumePictures(int value);
    void setMainUnderstandPictures(int value);
    void setWsTempPictures(int value);
    void setWsVolumePictures(int value);
    void setWsUnderstandPictures(int value);

    void on_tabAll_currentChanged(int index);
};

#endif // FRMSERVER_H
