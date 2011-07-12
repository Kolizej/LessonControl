#include "frmserver.h"
#include "ui_frmserver.h"
#include "QDesktopWidget"
#include "clsglobal.h"
#include "QPushButton"
#include "QCloseEvent"

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
    ci.s_lessonTemp = struct_list.value(1);
    ci.s_understanding = struct_list.value(2);
    ci.s_volume = struct_list.value(3);
    ci.s_status = struct_list.value(4);

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
            //���� ������
            ui->sldTemp->setValue(list_ci.at(i).s_lessonTemp.toInt());
            //�������� ���������
            ui->sldUnderstand->setValue(list_ci.at(i).s_understanding.toInt());
            //���������
            ui->sldVolume->setValue(list_ci.at(i).s_volume.toInt());
        }
    }
}

void frmServer::setMainParams()
{
    //������� ���� ������
    int m_temp = 0;
    //������� ���������
    int m_volume = 0;
    //������� �������� ���������
    int m_understand = 0;

    int list_cnt = list_ci.count();

    for(int i = 0;i<list_cnt;i++)
    {
        m_temp+=list_ci.at(i).s_lessonTemp.toInt();
        m_volume+=list_ci.at(i).s_volume.toInt();
        m_understand+=list_ci.at(i).s_understanding.toInt();
    }

    m_temp = m_temp/list_cnt;
    ui->slmTemp->setValue(m_temp);

    m_volume = m_volume/list_cnt;
    ui->slmVolume->setValue(m_volume);

    m_understand = m_understand/list_cnt;
    ui->slmUnderstand->setValue(m_understand);

    //������� ��������� ������
    int midUnderstand = m_understand/list_cnt;

    if(midUnderstand<=0.5)
        ui->slmLevel->setValue(0);
    else if((midUnderstand>0.5)&&(midUnderstand<=0.75))
        ui->slmLevel->setValue(1);
    else if((midUnderstand>0.75)&&(midUnderstand<=0.9))
        ui->slmLevel->setValue(2);
    else if(midUnderstand>0.9)
        ui->slmLevel->setValue(2);

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
                litem->setIcon(QIcon(":/icons/itemico/K001.ico"));
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
        res = msg.question(this,tr("����� � ��������"),tr("�� ������� �������� �����������. �� ����� ������ ������� ��������?"),QMessageBox::Yes,QMessageBox::No);

        if(res == QMessageBox::No)
        {
            ce->ignore();
        }
    }
    else
    {
        res = msg.question(this,tr("����� � ��������"),tr("������� ��������?"),QMessageBox::Yes,QMessageBox::No);

        if(res == QMessageBox::No)
        {
            ce->ignore();
        }
    }
}

void frmServer::on_listWorkstations_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(ui->listWorkstations->isItemSelected(current))
        setWorkstationParams(current->text());
}
