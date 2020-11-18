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

    didConnect();

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
    didConnect(); // no error checking
}

void Network::didRecieveData(){
    // 1-- read all avalaioble data from socket and append to buffer
    while(peerSocket->bytesAvailable()){
        //2-- read and analyze the byte being sent
        char c;
        peerSocket->getChar(&c);
        if(c == '\n'){
            //3-- we've recieved a message break

            //null terminate our buffer
            buffer.push_back('\0');

            //flush the buffer out as a C-style char* string
            char* message_char_arr = buffer.data();

            //cast the message into a QString, and grab the peer address
            emit didRecieveMessage(QString(message_char_arr), peerSocket->peerAddress().toString());

            //clear buffer
            buffer.clear();
        }
        else
        {
            //4
            buffer.push_back(c);
        }
    }

}

void Network::didConnect(){
    //Establish a connection to let us knwo when data is available to read
    connect(peerSocket, &QTcpSocket::readyRead, this, &Network::didRecieveData);
}

void Network::sendMessageToPeer(QString message){
    if(peerSocket != nullptr){
        //prepare message for sending by appending return
        message.append("/n"); //this will signify end of message

        //grab the data from the QString, in the form of QData*
        const QChar* data = message.constData();
        const int messageDataSize = message.size();

        //allocate a chat to hold our message
        char* messsageCharArr = (char*)calloc(messageDataSize, sizeof (char));

        //copy charcater by charcater from out data to our char* array
        for (int i=0; i<messageDataSize; i++){
            messsageCharArr[i] = data[i].toLatin1();//convert to ASCII
        }

        peerSocket->write(messsageCharArr, messageDataSize);

        //deallocate aray (to avoid memory leak)
        free(messsageCharArr);
    }
}
