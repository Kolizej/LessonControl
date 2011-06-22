#include <QtGui/QApplication>
#include "frmconnect.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmConnect w;
    w.show();

    return a.exec();
}
