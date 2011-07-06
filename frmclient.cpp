#include "frmclient.h"
#include "ui_frmclient.h"
#include "QDesktopWidget"
#include "QHostAddress"
#include "QHostInfo"
#include "clsglobal.h"
#include "QCloseEvent"

frmClient::frmClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmClient)
{
    ui->setupUi(this);
    moveWindowToCenter();
    sendMessage("online");
}

frmClient::~frmClient()
{
    delete ui;
}

void frmClient::moveWindowToCenter()
{
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
}

void frmClient::sendMessage(QString status)
{
    connectToServer(p_server,p_port.toUInt());
    cInfo.s_status = status;
    QByteArray array = makeMessageString().toAscii();
    str_message = array.data();

    client.write(str_message,100);

}

void frmClient::sendCloseMessage()
{
    sendMessage("offline");
}

void frmClient::connectToServer(QString server_adress, quint16 server_port)
{
    QHostAddress ha(server_adress);
    client.connectToHost(ha,server_port);
}

QString frmClient::makeMessageString()
{    
    QString res;
    cInfo.s_hostName = QHostInfo::localHostName();
    cInfo.s_lessonTemp = "1";
    cInfo.s_understanding = "2";
    cInfo.s_volume = "3";
    res+=cInfo.s_hostName+"|"+cInfo.s_lessonTemp+"|"+cInfo.s_understanding+"|"+cInfo.s_volume+"|"+cInfo.s_status;
    return res;
}

void frmClient::closeEvent(QCloseEvent *ce)
{
    sendCloseMessage();
    int res = msg.question(this,tr("Вихід з програми"),tr("Закрити програму?"),QMessageBox::Yes,QMessageBox::No);

    if(res == QMessageBox::No)
    {
        ce->ignore();
        sendMessage("online");
    }
}
