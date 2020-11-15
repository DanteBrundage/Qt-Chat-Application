#include "network.h"

Network::Network(QObject *parent) : QObject(parent)
{

    //initialize server
    this->server = new QTcpServer(this);

    //ask the server to listen
    //if it cannot listen, something out of my my conytol went wrong and I should exit
    if(!server->listen(QHostAddress::AnyIPv4, 25565)) {
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
