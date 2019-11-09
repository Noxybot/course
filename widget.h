#ifndef WIDGET_H
#define WIDGET_H

#include "formforadding.h"

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
    void on_pushButton_add_clicked();

    void on_pushButton_del_clicked();

    void on_tableView_clients_pressed(const QModelIndex &index);

    void on_tableView_clients_clicked(const QModelIndex &index);

    void on_addngWidget_ok_clicked(QString start_date, QString end_date, QString cred_card, int bike_id, int place_id);

    void on_pushButton_clicked();

    void on_reSelect_clients();

private:
    Ui::Widget *ui;
    QSqlDatabase db;

    QVector<QTreeView *> views;
    QSqlTableModel* bikes_model;
    QSqlTableModel* rental_places_model;
    QSqlTableModel* clients_model;
    QSqlTableModel* rent_agreements_model;
    QSqlTableModel* bikes_rent_places_model;


    QSqlQueryModel *clients_additional_model;

};
#endif // WIDGET_H
