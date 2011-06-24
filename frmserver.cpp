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
    //ui->listWidget->addItem((QString)buffer + " online");
    client->close();
}
