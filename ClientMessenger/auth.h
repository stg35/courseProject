#ifndef AUTH_H
#define AUTH_H
#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Auth;
}

class Auth : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор окна авторизации
     */
    explicit Auth(QWidget *parent = nullptr);
    ~Auth();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Auth *ui;
    MainWindow *window;
};

#endif // AUTH_H
