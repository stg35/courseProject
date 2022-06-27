#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTime>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор для окна чата
     * @param s: имя введенное пользователем
     * @param parent: родительское окно
     */
    MainWindow(QString s = "", QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_2_clicked();

    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray Data;
    /**
     * @brief Отправка данных на сервер
     * @param str: сообщение
     * @param name: имя пользователя
     */
    void SendToServer(QString str, QString name);
    quint16 nextBlockSize;
    QString username;

public slots:
    /**
     * @brief Функция, обрабатывающая входящие веб-сокеты
     */
    void slotReadyRead();
};
#endif // MAINWINDOW_H
