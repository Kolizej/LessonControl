#ifndef FRMCONNECT_H
#define FRMCONNECT_H

#include <QWidget>

namespace Ui {
    class frmConnect;
}

class frmConnect : public QWidget
{
    Q_OBJECT

public:
    explicit frmConnect(QWidget *parent = 0);
    ~frmConnect();

private:
    Ui::frmConnect *ui;
};

#endif // FRMCONNECT_H
