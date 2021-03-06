#include "frmconnect.h"
#include "ui_frmconnect.h"
#include "QDesktopWidget"
#include "frmclient.h"
#include "frmserver.h"
#include "clsglobal.h"
#include "QMessageBox"

frmConnect::frmConnect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmConnect)
{
    ui->setupUi(this);
    moveWindowToCenter();

    //����� ��� IP
    QRegExpValidator *v = new QRegExpValidator(this);
    QRegExp rx("((1{0,1}[0-9]{0,2}|2[0-4]{1,1}[0-9]{1,1}|25[0-5]{1,1})\\.){3,3}(1{0,1}[0-9]{0,2}|2[0-4]{1,1}[0-9]{1,1}|25[0-5]{1,1})");
    v->setRegExp(rx);
    ui->txtServer->setValidator(v);

    ui->txtPort->setValidator(new QIntValidator(0,65536,ui->txtPort));
}

frmConnect::~frmConnect()
{
    delete ui;
}

void frmConnect::on_chbCreateServer_stateChanged(int arg1)
{
    //�������� ���������� �������� �� �������
    if(arg1 == 0)
    {
        ui->txtServer->setEnabled(true);
        ui->txtServer->clear();
        ui->btnOk->setText(tr("ϳ����������"));
    }
    else
    {
        ui->txtServer->setText("127.0.0.1");
        ui->txtPort->setText("8888");
        ui->txtServer->setEnabled(false);
        ui->btnOk->setText(tr("��������"));
    }
}

void frmConnect::moveWindowToCenter()
{
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
}

bool frmConnect::testConnection(QString server_adress, quint16 server_port)
{
    bool res = true;
    return res;
}

void frmConnect::on_btnOk_clicked()
{
    QHostAddress adressValidator;

    if(adressValidator.setAddress(ui->txtServer->text()) && testConnection(ui->txtServer->text(),ui->txtPort->text().toUInt()))
    {
        p_server = ui->txtServer->text();
        p_port = ui->txtPort->text();

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
    else
    {
        QMessageBox msg;
        msg.warning(this,tr("�i���������"),tr("������ �����������, ��� ���i��i ��������� �i���������."),QMessageBox::Ok);
        ui->txtServer->setFocus();
    }
}
