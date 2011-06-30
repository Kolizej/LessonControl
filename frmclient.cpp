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

void frmClient::connectToServer(QString server_adress, quint16 server_port)
{
    QHostAddress ha(server_adress);
    client.connectToHost(ha,server_port);
}

void frmClient::sendMessage(QString message)
{
    connectToServer(p_server,p_port.toUInt());
    QByteArray array = message.toAscii();
    str_message = array.data();
    client.write(str_message,20);
}

QString frmClient::makeMessageString(ClientInfo *ci)
{
    QString res;
    res+=ci->s_hostName+"|"+ci->s_lessonTemp+"|"+ci->s_understanding+"|"+ci->s_volume+"|"+ci->s_status;
    return res;
}
