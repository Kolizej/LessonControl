#include "frmclient.h"
#include "ui_frmclient.h"
#include "QDesktopWidget"

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
