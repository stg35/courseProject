#include "server.h"

Server::Server()
{
    if(this->listen(QHostAddress::Any, 2323)) {
        qDebug() << "start";
    } else {
        qDebug() << "error";
    }
}

void Server::incomingConnection(qintptr socketDescriptor) {
    std::unique_ptr<QTcpSocket> socket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket.get(), &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket.get(), &QTcpSocket::disconnected, socket.get(), &QTcpSocket::deleteLater);
    Sockets.push_back(socket.get());
    qDebug() << "client connected: " << socketDescriptor;
}

void Server::slotReadyRead() {
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    if(in.status() == QDataStream::Ok) {
        qDebug() << "read...";
        QString str;
        in >> str;
        qDebug() << str;
        SendToClient(str);
    } else {
        qDebug() << "DataStream error";
    }
}

void Server::SendToClient(QString str) {
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out << str;
    for(size_t i = 0; i < Sockets.size(); i++) {
        Sockets[i]->write(Data);
    }
}
