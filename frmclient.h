#ifndef FRMCLIENT_H
#define FRMCLIENT_H

#include <QWidget>

namespace Ui {
    class frmClient;
}

class frmClient : public QWidget
{
    Q_OBJECT

public:
    explicit frmClient(QWidget *parent = 0);
    ~frmClient();

private:
    Ui::frmClient *ui;

private slots:
    void moveWindowToCenter();
};

#endif // FRMCLIENT_H
