#include "frmconnect.h"
#include "ui_frmconnect.h"

frmConnect::frmConnect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmConnect)
{
    ui->setupUi(this);
}

frmConnect::~frmConnect()
{
    delete ui;
}
