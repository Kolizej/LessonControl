#include "frmclient.h"
#include "ui_frmclient.h"

frmClient::frmClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmClient)
{
    ui->setupUi(this);
}

frmClient::~frmClient()
{
    delete ui;
}
