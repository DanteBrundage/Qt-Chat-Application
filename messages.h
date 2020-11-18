#ifndef MESSAGES_H
#define MESSAGES_H

#include <QObject>
#include "QStringListModel"

class Messages : public QStringListModel
{
    Q_OBJECT
public:
    Messages();
    void append(QString message);
public slots:
    void appendNetworkMessage(QString message, QString addressString);
};

#endif // MESSAGES_H
