#ifndef CLIENTINFORMATION_H
#define CLIENTINFORMATION_H

#include "QString"

//структура содержит всю информацию о текущем состоянии клиента
struct ClientInfo
{
    QString s_hostName; //имя хоста
    QString s_lessonTemp; //темп лекции
    QString s_understanding; //уровень понимания
    QString s_volume; //громкость
    QString s_status; //offline или online
};

#endif // CLIENTINFORMATION_H
