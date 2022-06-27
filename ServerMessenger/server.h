#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QTime>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    QTcpSocket *socket;

private:
    QVector<QTcpSocket*> Sockets;
    QByteArray Data;
    void SendToClient(QString str, QString name);

public slots:
    /**
     * @brief Обрабатывает входящие соединения
     * @param socketDescriptor: уникальный id веб-сокета
     */
    void incomingConnection(qintptr socketDescriptor);
    /**
     * @brief Обрабатывает входящие веб-сокеты
     */
    void slotReadyRead();

};

#endif // SERVER_H
