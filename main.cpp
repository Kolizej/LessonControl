#include <QtGui/QApplication>
#include "frmconnect.h"
#include "QLabel"
#include "QTextCodec"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    QApplication a(argc, argv);
    frmConnect w;
    w.show();

    return a.exec();
}
