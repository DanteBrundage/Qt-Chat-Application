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
};

#endif // MESSAGES_H
