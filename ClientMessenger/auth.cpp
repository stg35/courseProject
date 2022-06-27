#include "auth.h"
#include "ui_auth.h"
#include "mainwindow.h"
#include <QPixmap>

Auth::Auth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Auth)
{
    ui->setupUi(this);
    QPixmap pix(":/img/img/chat-logo.svg");
    int w = ui->image->width();
    int h = ui->image->height();

    ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

Auth::~Auth()
{
    delete ui;
}

void Auth::on_pushButton_clicked()
{
    window = new MainWindow(ui->inputName->text(), this);
    this->close();
    window->show();
}

