#ifndef CONNECTTODIALOG_H
#define CONNECTTODIALOG_H

#include <QDialog>
#include <QHostAddress>

namespace Ui {
class ConnectToDialog;
}

class ConnectToDialog : public QDialog
{
    Q_OBJECT
signals:
    void userIntendsConnection(QHostAddress address, quint64);
public:
    explicit ConnectToDialog(QWidget *parent = nullptr);
    ~ConnectToDialog();

private:
    Ui::ConnectToDialog *ui;
    void connectButtonPressed();
};

#endif // CONNECTTODIALOG_H
