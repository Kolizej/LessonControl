#ifndef CLIENTINFORMATION_H
#define CLIENTINFORMATION_H

#include "QString"

//��������� �������� ��� ���������� � ������� ��������� �������
struct ClientInfo
{
    QString s_hostName; //��� �����
    QString s_lessonTemp; //���� ������
    QString s_understanding; //������� ���������
    QString s_volume; //���������
    QString s_status; //offline ��� online
};

#endif // CLIENTINFORMATION_H
