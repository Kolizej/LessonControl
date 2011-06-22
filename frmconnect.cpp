#include "frmconnect.h"
#include "ui_frmconnect.h"
#include "QDesktopWidget"
#include "frmclient.h"
#include "frmserver.h"

frmConnect::frmConnect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmConnect)
{
    ui->setupUi(this);
    moveWindowToCenter();
}

frmConnect::~frmConnect()
{
    delete ui;
}

void frmConnect::on_chbCreateServer_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->txtServer->setEnabled(true);
        ui->txtPort->setEnabled(true);
        ui->btnOk->setText(tr("Connect"));
    }
    else
    {
        ui->txtServer->setEnabled(false);
        ui->txtPort->setEnabled(false);
        ui->btnOk->setText(tr("Create"));
    }
}

void frmConnect::moveWindowToCenter()
{
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
}

void frmConnect::on_btnOk_clicked()
{
    if(ui->chbCreateServer->isChecked())
    {
        frmServer *server_frm = new frmServer;
        server_frm->show();
    }
    else
    {
        frmClient *client_frm = new frmClient;
        client_frm->show();
    }
    this->close();
}
