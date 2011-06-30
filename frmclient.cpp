#include "frmclient.h"
#include "ui_frmclient.h"
#include "QDesktopWidget"
#include "QHostAddress"
#include "QHostInfo"
#include "clsglobal.h"

frmClient::frmClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmClient)
{
    ui->setupUi(this);
    moveWindowToCenter();
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

void frmClient::sendMessage()
{
    connectToServer(p_server,p_port.toUInt());
    QByteArray array = makeMessageString();
    str_message = array.data();
    client.write(str_message,20);
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
    res+=cInfo.s_hostName+"|"+cInfo.s_lessonTemp+"|"+cInfo.s_understanding+"|"+cInfo.s_volume+"|"+cInfo.s_status;
    return res;
}
