#ifndef WIDGET_H
#define WIDGET_H

#include "formforadding.h"
#include "formforsearchingclients.h"
#include "formforsearchingbikes.h"
#include "formforsearchingagreements.h"
#include "ClientInfo.h"

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QVector>
#include <QString>
#include <QSqlQueryModel>
#include <QTreeView>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void FindClients(ClientInfo info);
    void FilterClients(ClientInfo info);
    void show_search_clients(){
        auto tmp = new FormForSearchingClients();
        QObject::connect(tmp, SIGNAL(sendSearchInfo(ClientInfo)), this, SLOT(FindClients(ClientInfo)));
        QObject::connect(tmp, SIGNAL(sendFilterInfo(ClientInfo)), this, SLOT(FilterClients(ClientInfo)));
        QObject::connect(tmp, SIGNAL(destroyed()), this, SLOT(on_reSelect_clients()));

        tmp->show();
    }

    void FindBikes(BikeInfo info);
    void FilterBikes(BikeInfo info);
    void ReselectBikes() { bikes_model->setFilter("");
                           bikes_model->select();}
    void show_bikes_menu()
    {
        auto tmp = new FormForSearchingBikes();
        QObject::connect(tmp, SIGNAL(sendBikeSearchInfo(BikeInfo)), this, SLOT(FindBikes(BikeInfo)));
        QObject::connect(tmp, SIGNAL(sendBikeFilterInfo(BikeInfo)), this, SLOT(FilterBikes(BikeInfo)));
        QObject::connect(tmp, SIGNAL(destroyed()), this, SLOT(ReselectBikes()));
        tmp->show();
    }






   void FindAgreements(AgreementInfo info);
   void FilterAgreements(AgreementInfo info);
   void ReselectAgreements() { rent_agreements_model->setFilter("");
                               rent_agreements_model->select(); }

   void show_agreements_menu()
   {
       auto tmp = new FormForSearchingAgreements();
       QObject::connect(tmp, SIGNAL(sendSearchInfo(AgreementInfo)), this, SLOT(FindAgreements(AgreementInfo)));
       QObject::connect(tmp, SIGNAL(sendFilterInfo(AgreementInfo)), this, SLOT(FilterAgreements(AgreementInfo)));
       QObject::connect(tmp, SIGNAL(destroyed()), this, SLOT(ReselectAgreements()));
       tmp->show();
   }




    void on_pushButton_add_clicked();

    void on_pushButton_del_clicked();

    void on_tableView_clients_pressed(const QModelIndex &index);

    void on_tableView_clients_clicked(const QModelIndex &index);

    void on_addngWidget_ok_clicked(QString start_date, QString end_date, QString cred_card, int bike_id, int place_id);

    void on_pushButton_clicked();

    void on_reSelect_clients();

    void on_pushButton_execute_clicked();
    void on_tableView_bikes_clicked(const QModelIndex &index);


    void on_tableView_rent_agreement_clicked(const QModelIndex &index);

private:
    Ui::Widget *ui;
    QSqlDatabase db;

    //QVector<QTreeView *> views;
    QSqlTableModel* bikes_model;
    QSqlTableModel* rental_places_model;
    QSqlTableModel* clients_model;
    QSqlTableModel* rent_agreements_model;
    QSqlTableModel* bikes_rent_places_model;


    QSqlQueryModel *clients_additional_model;

};
#endif // WIDGET_H
