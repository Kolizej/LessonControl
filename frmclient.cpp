#include "frmclient.h"
#include "ui_frmclient.h"
#include "QDesktopWidget"
#include "QHostAddress"
#include "QHostInfo"
#include "clsglobal.h"
#include "QCloseEvent"
#include "clsenums.h"

frmClient::frmClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmClient)
{
    ui->setupUi(this);
    moveWindowToCenter();

    //начальные параметры для структуры
    cInfo.s_hostName = QHostInfo::localHostName();
    cInfo.s_understanding = clsEnums::Understand;
    cInfo.s_lessonTemp = clsEnums::SpeedNormal;
    cInfo.s_volume = clsEnums::VolumeNormal;
    cInfo.s_status = "online";

    sendMessage("online");
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

void frmClient::sendMessage(QString status)
{
    connectToServer(p_server,p_port.toUInt());
    cInfo.s_status = status;
    QByteArray array = makeMessageString().toAscii();
    str_message = array.data();

    client.write(str_message,100);

}

void frmClient::sendCloseMessage()
{
    sendMessage("offline");
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

void frmClient::closeEvent(QCloseEvent *ce)
{
    sendCloseMessage();
    int res = msg.question(this,tr("Вихід з програми"),tr("Закрити програму?"),QMessageBox::Yes,QMessageBox::No);

    if(res == QMessageBox::No)
    {
        ce->ignore();
        sendMessage("online");
    }
}

void frmClient::on_btnUnderstand_toggled(bool checked)
{
    if(checked)
    {
        ui->btnNotUnderstand->setChecked(false);
    }
    cInfo.s_understanding = QString::number(clsEnums::Understand);
    sendMessage("online");

}

void frmClient::on_btnNotUnderstand_toggled(bool checked)
{
    if(checked)
    {
        ui->btnUnderstand->setChecked(false);
    }
    cInfo.s_understanding = QString::number(clsEnums::NotUnderstand);
    sendMessage("online");
}

void frmClient::on_btnSpeedHigh_toggled(bool checked)
{
    if(checked)
    {
        ui->btnSpeedLow->setChecked(false);
        ui->btnSpeedNormal->setChecked(false);
    }
    cInfo.s_lessonTemp = QString::number(clsEnums::SpeedHigh);
    sendMessage("online");
}

void frmClient::on_btnSpeedNormal_toggled(bool checked)
{
    if(checked)
    {
        ui->btnSpeedLow->setChecked(false);
        ui->btnSpeedHigh->setChecked(false);
    }
    cInfo.s_lessonTemp = QString::number(clsEnums::SpeedNormal);
    sendMessage("online");
}

void frmClient::on_btnSpeedLow_toggled(bool checked)
{
    if(checked)
    {
        ui->btnSpeedNormal->setChecked(false);
        ui->btnSpeedHigh->setChecked(false);
    }
    cInfo.s_lessonTemp = QString::number(clsEnums::SpeedLow);
    sendMessage("online");
}

void frmClient::on_btnVolumeHigh_toggled(bool checked)
{
    if(checked)
    {
        ui->btnVolumeNormal->setChecked(false);
        ui->btnVolumeLow->setChecked(false);
    }
    cInfo.s_volume = QString::number(clsEnums::VolumeHigh);
    sendMessage("online");
}

void frmClient::on_btnVolumeNormal_toggled(bool checked)
{
    if(checked)
    {
        ui->btnVolumeHigh->setChecked(false);
        ui->btnVolumeLow->setChecked(false);
    }
    cInfo.s_volume = QString::number(clsEnums::VolumeNormal);
    sendMessage("online");
}

void frmClient::on_btnVolumeLow_toggled(bool checked)
{
    if(checked)
    {
        ui->btnVolumeNormal->setChecked(false);
        ui->btnVolumeHigh->setChecked(false);
    }
    cInfo.s_volume = QString::number(clsEnums::VolumeLow);
    sendMessage("online");
}
