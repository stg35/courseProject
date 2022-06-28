#define private public
#include <catch2/catch_all.hpp>
#include <QMainWindow>
#include <QDialog>
#include "../mainwindow.h"
#include "../auth.h"

TEST_CASE("Is username right?", "[username]")
{
    auto window = std::make_unique<MainWindow>("alex");
    REQUIRE((window->username) == "alex");
    REQUIRE((window ? true : false) == true);
}

TEST_CASE("Is window open?", "[window]")
{
    auto window = std::make_unique<Auth>();
    REQUIRE((window ? true : false) == true);
}

TEST_CASE("Check socket's data", "[socketData]")
{
    auto window = std::make_unique<MainWindow>("alex");
    window->SendToServer("Hello, World!", window->username);
    QDataStream in(window->socket);
    in.setVersion(QDataStream::Qt_6_2);
    QString str;
    QString name;
    QTime time;
    in >> time >> name >> str;
    REQUIRE(name == "alex");
    REQUIRE(str == "Hello, World!");
}
