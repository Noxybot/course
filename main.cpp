#include "widget.h"

#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget* w = new Widget;
    QMainWindow wind;
    wind.setCentralWidget(w);
    QMenuBar* menuBar = new QMenuBar();
    QMenu *mainMenu = new QMenu("Меню");
    menuBar->addMenu(mainMenu);

    QMenu *clientsMenu = new QMenu("Клиенты");

//    QMenu *clientsSortMenu = new QMenu("Сортировка");
//    clientsSortMenu->addAction("По возрастанию");
//    clientsSortMenu->addAction("По убыванию");

    QObject::connect(clientsMenu->addAction("Поиск / Фильтрация"), SIGNAL(triggered()), w, SLOT(show_search_clients()));
  //  clientsMenu->addMenu(clientsSortMenu);

    QMenu *bikesMenu = new QMenu("Велосипеды");
    QObject::connect(bikesMenu->addAction("Поиск / Фильтрация"), SIGNAL(triggered()), w, SLOT(show_bikes_menu()));

//    QMenu *bikesSortMenu = new QMenu("Сортировка");
//    bikesSortMenu->addAction("По возрастанию");
//    bikesSortMenu->addAction("По убыванию");

    bikesMenu->addAction("Статистика");
   // bikesMenu->addMenu(bikesSortMenu);

    QMenu *agreementsMenu = new QMenu("Договоры");

//    QMenu *agreementsSortMenu = new QMenu("Сортировка");
//    agreementsSortMenu->addAction("По возрастанию");
//    agreementsSortMenu->addAction("По убыванию");
//agreementsMenu->addMenu(agreementsSortMenu);

    QObject::connect(agreementsMenu->addAction("Поиск / Фильтрация"), SIGNAL(triggered()), w, SLOT(show_agreements_menu()));


    mainMenu->addMenu(clientsMenu);
    mainMenu->addMenu(bikesMenu);
    mainMenu->addMenu(agreementsMenu);

    QObject::connect(mainMenu->addAction("Выход"), SIGNAL(triggered()), &a, SLOT(quit()));
    wind.setMenuBar(menuBar);
    wind.show();
    return a.exec();
}
