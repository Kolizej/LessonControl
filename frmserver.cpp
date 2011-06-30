#include "frmserver.h"
#include "ui_frmserver.h"
#include "QDesktopWidget"

frmServer::frmServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmServer)
{
    ui->setupUi(this);
    moveWindowToCenter();
    connect(&server,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    server.listen(QHostAddress::Any,8888);
}

frmServer::~frmServer()
{
    server.close();
    delete ui;
}

void frmServer::moveWindowToCenter()
{
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
}

void frmServer::acceptConnection()
{
    client = server.nextPendingConnection();
    connect(client,SIGNAL(readyRead()),this,SLOT(startRead()));
}

void frmServer::startRead()
{
    char buffer[1024] = {0};
    client->read(buffer,client->bytesAvailable());
    parseMessage((QString)buffer);
    client->close();
}

void frmServer::parseMessage(QString message)
{
    QStringList struct_list =  message.split("|",QString::KeepEmptyParts);
    ci.s_hostName = struct_list.value(0);
    ci.s_lessonTemp = struct_list.value(1);
    ci.s_understanding = struct_list.value(2);
    ci.s_volume = struct_list.value(3);
    ci.s_status = struct_list.value(4);
    list_ci.append(ci);
    setParams();
}

void frmServer::setParams()
{
    ui->listWorkstations->clear();

    foreach(ClientInfo cip,list_ci)
    {
        ui->listWorkstations->addItem(cip.s_hostName);
    }
}
