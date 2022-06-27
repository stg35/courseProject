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
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    Sockets.push_back(socket);
    qDebug() << "client connected: " << socketDescriptor;
}

void Server::slotReadyRead() {
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok) {
        qDebug() << "read...";
        QString str;
        QString name;
        QTime time;
        in >> time >> name >> str;
        qDebug() << str << " " << name;
        SendToClient(str, name);
    } else {
        qDebug() << "DataStream error";
    }
}

void Server::SendToClient(QString str, QString name) {
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << QTime::currentTime() << name << str;
    for(size_t i = 0; i < Sockets.size(); i++) {
        Sockets[i]->write(Data);
    }
}
