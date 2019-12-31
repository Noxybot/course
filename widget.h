#ifndef WIDGET_H
#define WIDGET_H

#include "formforadding.h"
#include "formforsearchingclients.h"
#include "formforsearchingbikes.h"
#include "formforsearchingagreements.h"
#include "formforaddingbikes.h"
#include "formforaddingrentplace.h"
#include "formforagrstats.h"
#include "formforagrstats2.h" // expired + by date
#include "formforclientsstats.h"
#include "ClientInfo.h"
#include "formforsendingreport.h"
#include <QDebug>

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QVector>
#include <QString>
#include <QSqlQueryModel>
#include <QTreeView>
#include <QTextStream>
#include <QDate>
#include <QPrinter>
#include <QTextDocument>
#include <QPrintDialog>

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

    void on_addngWidget_ok_clicked(QString start_date, QString end_date, QString cred_card, int bike_id, int place_id, int sum);

    void on_pushButton_clicked();

    void on_reSelect_clients();

    void on_pushButton_execute_clicked();
    void on_tableView_bikes_clicked(const QModelIndex &index);


    void on_tableView_rent_agreement_clicked(const QModelIndex &index);

    void ShowStats()
    {
        auto t = new FormForAgrStats();
        t->show();
    }

    void ShowStatsForAgrs2()
    {
        auto t = new FormForAgrStats2();
        t->show();
    }

    void ShowClientsStats()
    {
        auto t = new FormForClientsStats;
        t->show();
    }


    void AddBike(BikeInfo info, bool adding);
    void AddRentPlace(RentPlaceInfo info, bool adding);




    void PrintAgreements()
    {
        QString strStream;
        QTextStream out(&strStream);
        QString title = "Отчет за месяц";
        QDate date = QDate::currentDate();
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("select * from rent_agreemnts;");
        const int rowCount = model->rowCount();
        const int columnCount = model->columnCount();

        out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg(title)
            <<  "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"
             << QString("<p align=center><span style=font-size:20.25pt;>%1</span></p>\n").arg(title)
                << QString("<p align=center><span style=font-size:20.25pt;>%1</span></p>\n").arg(date.toString())
            <<"<table border=1 cellspacing=0 cellpadding=1 width=100%>\n";

        out << "<thead><tr bgcolor=#f0f0f0>";
        for (int column = 0; column < columnCount; column++)
                out << QString("<th>%1</th>").arg(model->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++) {
            out << "<tr>";
            for (int column = 0; column < columnCount; column++) {
                    QString data = model->data(model->index(row, column)).toString().simplified();
                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
            out << "</tr>\n";
        }
        out <<  "</table>\n"
            "</body>\n"
            "</html>\n";

        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);
        qDebug() << strStream;

        QPrinter printer;

        QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
        if (dialog->exec() == QDialog::Accepted) {
            document->print(&printer);
        }

        delete document;
    }
    void SendReport()
    {
        auto t = new FormForSendingReport();
        t->show();
    }


    void on_pushButton_print_check_clicked();

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
