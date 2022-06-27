#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QString s, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , username(s)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    socket->connectToHost("127.0.0.1", 2323);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok) {
        QString str;
        QString name;
        QTime time;
        in >> time >> name >> str;
        ui->textBrowser->append(time.toString() + " @" + name + ": " + str);
    } else {
        ui->textBrowser->append("read error!");
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    SendToServer(ui->lineEdit->text(), username);
}


void MainWindow::on_lineEdit_returnPressed()
{
    SendToServer(ui->lineEdit->text(), username);
}

void MainWindow::SendToServer(QString str, QString name)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << QTime::currentTime() << name << str;
    socket->write(Data);
    ui->lineEdit->clear();
}

