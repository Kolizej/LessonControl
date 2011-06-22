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

private slots:
    void on_chbCreateServer_stateChanged(int arg1);
    void moveWindowToCenter();

    void on_btnOk_clicked();

private:
    Ui::frmConnect *ui;
};

#endif // FRMCONNECT_H
