#include "frmserver.h"
#include "ui_frmserver.h"
#include "QDesktopWidget"
#include "clsglobal.h"
#include "QPushButton"
#include "QCloseEvent"
#include "clsenums.h"

frmServer::frmServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmServer)
{
    ui->setupUi(this);
    moveWindowToCenter();
    connect(&server,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    server.listen(QHostAddress::Any,p_port.toUInt());
    setParams();
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

bool frmServer::isClientInfoExists(ClientInfo clInf)
{
    bool res = false;

    for(int i = 0;i<list_ci.count();i++)
    {
        if(list_ci.at(i).s_hostName == clInf.s_hostName)
            return true;
    }

    return res;
}

void frmServer::parseMessage(QString message)
{
    QStringList struct_list =  message.split("|",QString::KeepEmptyParts);
    ci.s_hostName = struct_list.value(0);
    ci.s_ipadress = struct_list.value(1);
    ci.s_lessonTemp = struct_list.value(2);
    ci.s_understanding = struct_list.value(3);
    ci.s_volume = struct_list.value(4);
    ci.s_status = struct_list.value(5);
    ci.s_isCalled = struct_list.value(6);

    if(ci.s_status == "online")
    {
        if(!isClientInfoExists(ci))
        {
            list_ci.append(ci);
        }
        else
        {
            for(int i = 0;i<list_ci.count();i++)
            {
                if(list_ci.at(i).s_hostName == ci.s_hostName)
                {
                    list_ci.replace(i,ci);
                }
            }
        }
    }
    else
    {
        for(int i = 0;i<list_ci.count();i++)
        {
            if(list_ci.at(i).s_hostName == ci.s_hostName)
            {
                list_ci.removeAt(i);
            }
        }

    }

    setParams();
}

void frmServer::setWorkstationParams(QString wsname)
{
    for(int i = 0;i<list_ci.count();i++)
    {
        if(list_ci.at(i).s_hostName == wsname)
        {
            //темп лекции
            int temp = list_ci.at(i).s_lessonTemp.toInt();
            ui->sldTemp->setValue(temp);
            setWsTempPictures(temp);

            //усвоение материала
            int und = list_ci.at(i).s_understanding.toInt();
            ui->sldUnderstand->setValue(und);
            setWsUnderstandPictures(und);

            //громкость
            int volume = list_ci.at(i).s_volume.toInt();
            ui->sldVolume->setValue(volume);
            setWsVolumePictures(volume);

        }
    }
}

//установка картинок для главной формы на темп
void frmServer::setMainTempPictures(int value)
{
    if(value ==0)
    {
        ui->mimgTempDown->setEnabled(true);
        ui->mimgTempNormal->setEnabled(false);
        ui->mimgTempDown->setEnabled(false);
    }
    else if(value == 1)
    {
        ui->mimgTempDown->setEnabled(false);
        ui->mimgTempNormal->setEnabled(true);
        ui->mimgTempDown->setEnabled(false);
    }
    else if(value == 2)
    {
        ui->mimgTempDown->setEnabled(false);
        ui->mimgTempNormal->setEnabled(false);
        ui->mimgTempDown->setEnabled(true);
    }
}

//установка картинок для главной формы на понимание
void frmServer::setMainUnderstandPictures(int value)
{
    if(value ==0)
    {
        ui->mimgIsUnd->setEnabled(false);
        ui->mimgIsNotUnd->setEnabled(true);
    }
    else if(value == 1)
    {
        ui->mimgIsUnd->setEnabled(true);
        ui->mimgIsNotUnd->setEnabled(false);
    }
}

//установка картинок для главной формы на звук
void frmServer::setMainVolumePictures(int value)
{
    if(value ==0)
    {
        ui->mimgVolumeDown->setEnabled(true);
        ui->mimgVolumeNormal->setEnabled(false);
        ui->mimgVolumeUp->setEnabled(false);
    }
    else if(value == 1)
    {
        ui->mimgVolumeDown->setEnabled(false);
        ui->mimgVolumeNormal->setEnabled(true);
        ui->mimgVolumeUp->setEnabled(false);
    }
    else if(value == 2)
    {
        ui->mimgVolumeDown->setEnabled(false);
        ui->mimgVolumeNormal->setEnabled(false);
        ui->mimgVolumeUp->setEnabled(true);
    }
}

//установка картинок для детальной формы на темп
void frmServer::setWsTempPictures(int value)
{
    if(value ==0)
    {
        ui->dimgTempDown->setEnabled(true);
        ui->dimgTempNormal->setEnabled(false);
        ui->dimgTempUp->setEnabled(false);
    }
    else if(value == 1)
    {
        ui->dimgTempDown->setEnabled(false);
        ui->dimgTempNormal->setEnabled(true);
        ui->dimgTempUp->setEnabled(false);
    }
    else if(value == 2)
    {
        ui->dimgTempDown->setEnabled(false);
        ui->dimgTempNormal->setEnabled(false);
        ui->dimgTempUp->setEnabled(true);
    }
}

//установка картинок для детальной формы на понимание
void frmServer::setWsUnderstandPictures(int value)
{
    if(value ==0)
    {
        ui->dimgIsUnd->setEnabled(false);
        ui->dimgIsNotUnd->setEnabled(true);
    }
    else if(value == 1)
    {
        ui->dimgIsUnd->setEnabled(true);
        ui->dimgIsNotUnd->setEnabled(false);
    }
}

//установка картинок для детальной формы на звук
void frmServer::setWsVolumePictures(int value)
{
    if(value ==0)
    {
        ui->dimgVolumeDown->setEnabled(true);
        ui->dimgVolumeNormal->setEnabled(false);
        ui->dimgVolumeUp->setEnabled(false);
    }
    else if(value == 1)
    {
        ui->dimgVolumeDown->setEnabled(false);
        ui->dimgVolumeNormal->setEnabled(true);
        ui->dimgVolumeUp->setEnabled(false);
    }
    else if(value == 2)
    {
        ui->dimgVolumeDown->setEnabled(false);
        ui->dimgVolumeNormal->setEnabled(false);
        ui->dimgVolumeUp->setEnabled(true);
    }
}


//установка параметров для главной формы
void frmServer::setMainParams()
{
    //средний темп лекции
    float m_temp = 0;
    //средняя громкость
    float m_volume = 0;
    //среднее усвоение материала
    float m_understand = 0;

    int list_cnt = list_ci.count();

    for(int i = 0;i<list_cnt;i++)
    {
        m_temp+=list_ci.at(i).s_lessonTemp.toInt();
        m_volume+=list_ci.at(i).s_volume.toInt();
        m_understand+=list_ci.at(i).s_understanding.toInt();
    }

    m_temp = m_temp/list_cnt;

    QString str_temp;
    str_temp.setNum(m_temp,'g',0);
    int temp = str_temp.toInt();
    ui->slmTemp->setValue(temp);
    setMainTempPictures(temp);

    m_volume = m_volume/list_cnt;

    QString str_volume;
    str_volume.setNum(m_volume,'g',0);
    int volume = str_volume.toInt();
    ui->slmVolume->setValue(volume);
    setMainVolumePictures(volume);

    m_understand = m_understand/list_cnt;

    QString str_understand;
    str_understand.setNum(m_understand,'g',0);
    int und = str_understand.toInt();
    ui->slmVolume->setValue(und);
    setMainUnderstandPictures(und);


    //уровень понимания группы
    if(m_understand<=0.5)
        ui->slmLevel->setValue(0);
    else if((m_understand>0.5)&&(m_understand<=0.75))
        ui->slmLevel->setValue(1);
    else if((m_understand>0.75)&&(m_understand<=0.9))
        ui->slmLevel->setValue(2);
    else if(m_understand>0.9)
        ui->slmLevel->setValue(3);

}

void frmServer::sendMessage(QString message_, QString host)
{
    uint prt = p_port.toUInt()+1;
    connectToServer(host,prt);
    QByteArray array = message_.toAscii();
    str_message = array.data();

    client_add.write(str_message,100);
}

void frmServer::connectToServer(QString server_adress, quint16 server_port)
{
    QHostAddress ha(server_adress);
    client_add.connectToHost(ha,server_port);
}

void frmServer::on_btnCall_clicked()
{
    ClientInfo ci_row;
    ci_row.s_hostName = list_ci.at(ui->listWorkstations->currentRow()).s_hostName;
    ci_row.s_ipadress = list_ci.at(ui->listWorkstations->currentRow()).s_ipadress;
    ci_row.s_isCalled = "true";
    ci_row.s_lessonTemp = list_ci.at(ui->listWorkstations->currentRow()).s_lessonTemp;
    ci_row.s_status = list_ci.at(ui->listWorkstations->currentRow()).s_status;
    ci_row.s_understanding = list_ci.at(ui->listWorkstations->currentRow()).s_understanding;
    ci_row.s_volume = list_ci.at(ui->listWorkstations->currentRow()).s_volume;

    list_ci.replace(ui->listWorkstations->currentRow(),ci_row);

    ui->listWorkstations->currentItem()->setIcon(QIcon(":/icons/itemico/bell.png"));

    QString _hostadress = ci_row.s_ipadress;
    sendMessage("true",_hostadress);
}

void frmServer::on_btnCallCancel_clicked()
{
    ClientInfo ci_row;
    ci_row.s_hostName = list_ci.at(ui->listWorkstations->currentRow()).s_hostName;
    ci_row.s_ipadress = list_ci.at(ui->listWorkstations->currentRow()).s_ipadress;
    ci_row.s_isCalled = "false";
    ci_row.s_lessonTemp = list_ci.at(ui->listWorkstations->currentRow()).s_lessonTemp;
    ci_row.s_status = list_ci.at(ui->listWorkstations->currentRow()).s_status;
    ci_row.s_understanding = list_ci.at(ui->listWorkstations->currentRow()).s_understanding;
    ci_row.s_volume = list_ci.at(ui->listWorkstations->currentRow()).s_volume;

    list_ci.replace(ui->listWorkstations->currentRow(),ci_row);

    ui->listWorkstations->currentItem()->setIcon(QIcon(":/icons/itemico/workstation.png"));

    QString _hostadress = ci_row.s_ipadress;
    sendMessage("false",_hostadress);
}

void frmServer::setDefaultParams()
{
    ui->slmLevel->setValue(0);
    ui->slmTemp->setValue(1);
    ui->slmUnderstand->setValue(1);
    ui->slmVolume->setValue(1);
    ui->sldTemp->setValue(0);
    ui->sldUnderstand->setValue(0);
    ui->sldVolume->setValue(0);
    ui->tabDetail->setEnabled(false);
}

void frmServer::setParams()
{
    ui->listWorkstations->clear();

    if(list_ci.count()>0)
    {
        ui->tabDetail->setEnabled(true);

        foreach(ClientInfo cip,list_ci)
        {
            if(cip.s_status == "online")
            {
                QListWidgetItem *litem = new QListWidgetItem(ui->listWorkstations);

                if(cip.s_isCalled == "true")
                    litem->setIcon(QIcon(":/icons/itemico/bell.png"));
                else
                    litem->setIcon(QIcon(":/icons/itemico/workstation.png"));

                litem->setText(cip.s_hostName);
                ui->listWorkstations->addItem(litem);
            }
        }
        setMainParams();

        if(ui->listWorkstations->count()>0)
        {
            if(ui->listWorkstations->selectedItems().count()>0)
                setWorkstationParams(ui->listWorkstations->selectedItems().first()->text());
        }
    }
    else
    {
        setDefaultParams();
    }

    ui->lblCount->setText(QString::number(ui->listWorkstations->count()));


}

void frmServer::closeEvent(QCloseEvent *ce)
{
    int res;

    if(ui->listWorkstations->count()>0)
    {
        res = msg.question(this,tr("Вихід з програми"),tr("До серверу підключені користувачі. Ви дійсно хочете закрити програму?"),QMessageBox::Yes,QMessageBox::No);

        if(res == QMessageBox::No)
        {
            ce->ignore();
        }
    }
    else
    {
        res = msg.question(this,tr("Вихід з програми"),tr("Закрити програму?"),QMessageBox::Yes,QMessageBox::No);

        if(res == QMessageBox::No)
        {
            ce->ignore();
        }
    }
}

void frmServer::on_listWorkstations_currentRowChanged(int currentRow)
{
    QListWidgetItem *wi = ui->listWorkstations->item(currentRow);

    if(wi!=0x0)
    {
        setMainParams();
        QString ws_name = ui->listWorkstations->item(currentRow)->text();
        setWorkstationParams(ws_name);
    }
}

void frmServer::on_tabAll_currentChanged(int index)
{
    int temp_up = 0;
    int temp_norm = 0;
    int temp_down = 0;
    int volume_up = 0;
    int volume_norm = 0;
    int volume_down = 0;
    int und = 0;
    int notUnd = 0;

    if(index == 2)
    {
        for(int i = 0;i<list_ci.count();i++)
        {
            //темп
            if(list_ci.at(i).s_lessonTemp.toInt() == 0)
            {
                temp_down++;
            }
            if(list_ci.at(i).s_lessonTemp.toInt() == 1)
            {
                temp_norm++;
            }
            if(list_ci.at(i).s_lessonTemp.toInt() == 2)
            {
                temp_up++;
            }

            //громкость
            if(list_ci.at(i).s_volume.toInt() == 0)
            {
                volume_down++;
            }
            if(list_ci.at(i).s_volume.toInt() == 1)
            {
                volume_norm++;
            }
            if(list_ci.at(i).s_volume.toInt() == 2)
            {
                volume_up++;
            }

            //понимание
            if(list_ci.at(i).s_understanding.toInt() == 0)
            {
                notUnd++;
            }
            if(list_ci.at(i).s_understanding.toInt() == 1)
            {
                und++;
            }
        }

        QString txt;
        txt = tr("Швидко: ")+QString::number(temp_up)+tr(" робочих станцiй");
        ui->lblTempUp->setText(txt);
        txt = tr("Норма: ")+QString::number(temp_norm)+tr(" робочих станцiй");
        ui->lblTempNormal->setText(txt);
        txt = tr("Повiльно ")+QString::number(temp_down)+tr(" робочих станцiй");
        ui->lblTempDown->setText(txt);

        txt = tr("Голосно: ")+QString::number(volume_up)+tr(" робочих станцiй");
        ui->lblVolumeUp->setText(txt);
        txt = tr("Норма: ")+QString::number(volume_norm)+tr(" робочих станцiй");
        ui->lblVolumeNormal->setText(txt);
        txt = tr("Тихо: ")+QString::number(volume_down)+tr(" робочих станцiй");
        ui->lblVolumeDown->setText(txt);

        txt = tr("Зрозумiло: ")+QString::number(und)+tr(" робочих станцiй");
        ui->LblUnd->setText(txt);
        txt = tr("Не зрозумiло: ")+QString::number(notUnd)+tr(" робочих станцiй");
        ui->lblDontUnd->setText(txt);
    }
}
