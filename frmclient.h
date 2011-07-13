#ifndef FRMCLIENT_H
#define FRMCLIENT_H

#include <QWidget>
#include <QtNetwork>
#include "ClientInformation.h"
#include "QMessageBox"
#include "QtNetwork/QTcpServer"
#include "QtNetwork/QTcpSocket"

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
    QTcpServer serverOnClient;
    QTcpSocket *clientForCall;
    char* str_message;
    ClientInfo cInfo;
    QMessageBox msg;

protected:
    void closeEvent(QCloseEvent *ce);

private slots:
    void moveWindowToCenter();
    void sendMessage(QString status);
    void connectToServer(QString server_adress, quint16 server_port);
    void sendCloseMessage();
    QString makeMessageString();    
    void on_btnUnderstand_toggled(bool checked);
    void on_btnNotUnderstand_toggled(bool checked);
    void on_btnSpeedHigh_toggled(bool checked);
    void on_btnSpeedNormal_toggled(bool checked);
    void on_btnSpeedLow_toggled(bool checked);
    void on_btnVolumeHigh_toggled(bool checked);
    void on_btnVolumeNormal_toggled(bool checked);
    void on_btnVolumeLow_toggled(bool checked);
    void acceptServerConnections();
    void startRead();
    void parseMessage(QString message);
    QString getLocalIP();
};

#endif // FRMCLIENT_H
