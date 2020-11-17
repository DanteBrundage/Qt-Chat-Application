#ifndef CONNECTTODIALOG_H
#define CONNECTTODIALOG_H

#include <QDialog>

namespace Ui {
class ConnectToDialog;
}

class ConnectToDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectToDialog(QWidget *parent = nullptr);
    ~ConnectToDialog();

private:
    Ui::ConnectToDialog *ui;
};

#endif // CONNECTTODIALOG_H
