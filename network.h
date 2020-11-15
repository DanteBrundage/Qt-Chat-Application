#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Network: public QObject
{
    Q_OBJECT
public:
    explicit Network(QObject *parent = nullptr);
private:
    QTcpServer* server;
    QTcpSocket* peerSocket;
signals:

private slots:
    void didRecieveClientConnection();

};

#endif // NETWORK_H
