#include "frmserver.h"
#include "ui_frmserver.h"
#include "QDesktopWidget"
#include "clsglobal.h"

frmServer::frmServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmServer)
{
    ui->setupUi(this);
    moveWindowToCenter();
    connect(&server,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    server.listen(QHostAddress::Any,p_port.toUInt());
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

    if(ci.s_status == "online")
    {
        list_ci.append(ci);
    }
    else
    {
        for(int i = 0;i<list_ci.count();i++)
        {
            if((list_ci.at(i).s_hostName == ci.s_hostName)&& (ci.s_status == "offline"))
            {
                list_ci.removeAt(i);
            }
        }
    }

    setParams();
}

void frmServer::setParams()
{
    ui->listWorkstations->clear();

    foreach(ClientInfo cip,list_ci)
    {
        if(cip.s_status == "online")
        {
            QListWidgetItem *litem = new QListWidgetItem(ui->listWorkstations);
            litem->setIcon(QIcon(":/icons/itemico/K001.ico"));
            litem->setText(cip.s_hostName);
            ui->listWorkstations->addItem(litem);
        }
    }

    ui->lblCount->setText(QString::number(ui->listWorkstations->count()));
}
