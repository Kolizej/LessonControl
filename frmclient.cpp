#include "frmclient.h"
#include "ui_frmclient.h"
#include "QDesktopWidget"
#include "QHostAddress"
#include "QHostInfo"
#include "clsglobal.h"
#include "QCloseEvent"
#include "clsenums.h"
#include "QNetworkInterface"

frmClient::frmClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmClient)
{
    ui->setupUi(this);

    //переместим окно в центр экрана
    moveWindowToCenter();

    //слушающий сервер (для метода вызова)
    connect(&serverOnClient,SIGNAL(newConnection()),this,SLOT(acceptServerConnections()));
    QHostAddress ha(p_server);
    serverOnClient.listen(ha,p_port.toUInt()+1);

    //начальные параметры для структуры сообщения
    cInfo.s_ipadress = getLocalIP();
    cInfo.s_hostName = QHostInfo::localHostName();
    cInfo.s_understanding = QString::number(clsEnums::Understand);
    cInfo.s_lessonTemp = QString::number(clsEnums::SpeedNormal);
    cInfo.s_volume = QString::number(clsEnums::VolumeNormal);
    cInfo.s_status = "online";

    //установка названия рабочего места
    ui->lblWorkstation->setText(QHostInfo::localHostName());

    //посылаем серверу сообщение, что рабочая станция в сети
    sendMessage("online");
}

frmClient::~frmClient()
{
    delete ui;
}

QString frmClient::getLocalIP()
{
    QString res;
    QList<QHostAddress> hosts = QNetworkInterface::allAddresses();
    hosts.removeOne(QHostAddress(0x7f000001));

    for(int i = 0;i<hosts.count();i++)
    {
        res = hosts[i].toString();
    }

    return res;
}

//перемещает окно в центр экрана
void frmClient::moveWindowToCenter()
{
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
}

//слот читает данные из сокета
void frmClient::startRead()
{
    char buffer[1024] = {0};
    clientForCall->read(buffer,clientForCall->bytesAvailable());
    parseMessage((QString)buffer);
    clientForCall->close();
}

//слот обрабатывает входящие подключения
void frmClient::acceptServerConnections()
{
    clientForCall = serverOnClient.nextPendingConnection();
    connect(clientForCall,SIGNAL(readyRead()),this,SLOT(startRead()));
}

//слот разбирает тип входящего сообщения и устанавливает реакцию на него
void frmClient::parseMessage(QString message)
{
    if(message == "true")
    {
        ui->indicator->setStyleSheet("QLineEdit {background-color: red}");
    }
    else if (message == "false")
    {
        ui->indicator->setStyleSheet("QLineEdit {background-color: green}");
    }
}

//слот отсылки сообщений
void frmClient::sendMessage(QString status)
{
    connectToServer(p_server,p_port.toUInt());
    cInfo.s_status = status;
    QByteArray array = makeMessageString().toAscii();

    str_message = array.data();

    client.write(str_message,100);

}

//слот отсылки сообщения о закрытии приложения
void frmClient::sendCloseMessage()
{
    sendMessage("offline");
}

//слот для подключения к серверу
void frmClient::connectToServer(QString server_adress, quint16 server_port)
{
    QHostAddress ha(server_adress);
    client.connectToHost(ha,server_port);    
}

//слот создает строку сообщения в необходимом формате
QString frmClient::makeMessageString()
{    
    QString res;
    cInfo.s_hostName = QHostInfo::localHostName();
    res+=cInfo.s_hostName+"|"+cInfo.s_ipadress+"|"+cInfo.s_lessonTemp+"|"+cInfo.s_understanding+"|"+cInfo.s_volume+"|"+cInfo.s_status;
    return res;
}

//реакция на закрытие приложения
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

//обработчик кнопки "Понятно"
void frmClient::on_btnUnderstand_toggled(bool checked)
{
    if(checked)
    {
        ui->btnNotUnderstand->setChecked(false);
        cInfo.s_understanding = QString::number(clsEnums::Understand);
        sendMessage("online");
    }
}

//обработчик кнопки "Не понятно"
void frmClient::on_btnNotUnderstand_toggled(bool checked)
{
    if(checked)
    {
        ui->btnUnderstand->setChecked(false);
        cInfo.s_understanding = QString::number(clsEnums::NotUnderstand);
        sendMessage("online");
    }    
}

//обработчик кнопки "Быстро"
void frmClient::on_btnSpeedHigh_toggled(bool checked)
{
    if(checked)
    {
        ui->btnSpeedLow->setChecked(false);
        ui->btnSpeedNormal->setChecked(false);
        cInfo.s_lessonTemp = QString::number(clsEnums::SpeedHigh);
        sendMessage("online");
    }    
}

//обработчик кнопки "Нормально" (скорость)
void frmClient::on_btnSpeedNormal_toggled(bool checked)
{
    if(checked)
    {
        ui->btnSpeedLow->setChecked(false);
        ui->btnSpeedHigh->setChecked(false);
        cInfo.s_lessonTemp = QString::number(clsEnums::SpeedNormal);
        sendMessage("online");
    }    
}

//обработчик кнопки "Медленно"
void frmClient::on_btnSpeedLow_toggled(bool checked)
{
    if(checked)
    {
        ui->btnSpeedNormal->setChecked(false);
        ui->btnSpeedHigh->setChecked(false);
        cInfo.s_lessonTemp = QString::number(clsEnums::SpeedLow);
        sendMessage("online");
    }    
}

//обработчик кнопки "Громко"
void frmClient::on_btnVolumeHigh_toggled(bool checked)
{
    if(checked)
    {
        ui->btnVolumeNormal->setChecked(false);
        ui->btnVolumeLow->setChecked(false);
        cInfo.s_volume = QString::number(clsEnums::VolumeHigh);
        sendMessage("online");
    }    
}

//обработчик кнопки "Нормально" (громкость)
void frmClient::on_btnVolumeNormal_toggled(bool checked)
{
    if(checked)
    {
        ui->btnVolumeHigh->setChecked(false);
        ui->btnVolumeLow->setChecked(false);
        cInfo.s_volume = QString::number(clsEnums::VolumeNormal);
        sendMessage("online");
    }    
}

//обработчик кнопки "Тихо"
void frmClient::on_btnVolumeLow_toggled(bool checked)
{
    if(checked)
    {
        ui->btnVolumeNormal->setChecked(false);
        ui->btnVolumeHigh->setChecked(false);
        cInfo.s_volume = QString::number(clsEnums::VolumeLow);
        sendMessage("online");
    }    
}
