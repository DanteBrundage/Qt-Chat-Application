#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Network: public QObject
{
    Q_OBJECT
public:
    explicit Network(quint64 port, QObject *parent = nullptr);
private:
    QTcpServer* server;
    QTcpSocket* peerSocket;
signals:
public slots:
    void  connectToClient(QHostAddress address, quint64 port);
private slots:
    void didRecieveClientConnection();

};

#endif // NETWORK_H
