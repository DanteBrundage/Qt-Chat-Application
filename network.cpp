#include "network.h"

Network::Network(quint64 port, QObject *parent) : QObject(parent)
{

    //initialize server
    this->server = new QTcpServer(this);

    //ask the server to listen
    //if it cannot listen, something out of my my conytol went wrong and I should exit
    if(!server->listen(QHostAddress::AnyIPv4, port)) {
        qDebug() << "Could not initialize Network layer server, exiting";
        //server->close();
        exit(-1);
    }

    connect(server, &QTcpServer::newConnection, this, &Network::didRecieveClientConnection);
}

void Network::didRecieveClientConnection() {
    qDebug() << "Did recieve client connection";

    //set peer socket
    peerSocket = this->server->nextPendingConnection();
    //close the server
    //this will prevent any further connection
    server->close();
}

void Network::connectToClient(QHostAddress address, quint64 port){
    //close our server for incoming connections, since we are starting an outgoing connection
    //Note: no error checking, we assume we input a valid and active IP and port
    server->close();

    //create a new peerSocket
    this->peerSocket = new QTcpSocket();

    qDebug() << "Attempting outgoing connection";
    peerSocket->connectToHost(address, port);
}
