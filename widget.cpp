#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>
#include "formforediting.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("178.150.141.36");
    db.setDatabaseName("bike_rent");
    db.setUserName("eduard");
    db.setPassword("Andyou33");
    if (!db.open())
        qDebug() << db.lastError().text();

    else
        qDebug() << "Success!";

    bikes_model = new QSqlTableModel(this, db);
    rental_places_model = new QSqlTableModel(this, db);
    clients_model = new QSqlTableModel(this, db);
    rent_agreements_model = new QSqlTableModel(this, db);
    bikes_rent_places_model = new QSqlTableModel(this, db);
    clients_additional_model = new QSqlQueryModel;


    bikes_model->setTable("bikes");
    rental_places_model->setTable("rental_places");
    clients_model->setTable("clients");
    rent_agreements_model->setTable("rent_agreemnts");
    bikes_rent_places_model->setTable("bike_rent_place");

    bikes_model->select();
    rental_places_model->select();
    clients_model->select();
    rent_agreements_model->select();
    bikes_rent_places_model->select();

    ui->tableView_bikes->setModel(bikes_model);
    ui->tableView_rent_places->setModel(rental_places_model);
    ui->tableView_additional_clients->setModel(clients_additional_model);
    ui->tableView_clients->setModel(clients_model);
    ui->tableView_rent_agreement->setModel(rent_agreements_model);
    ui->tableView_bike_rent_place->setModel(bikes_rent_places_model);

    ui->tableView_bikes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_rent_places->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_clients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_additional_clients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_rent_agreement->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_bike_rent_place->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView_bikes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_rent_places->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_clients->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_additional_clients->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_rent_agreement->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_bike_rent_place->setSelectionBehavior(QAbstractItemView::SelectRows);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_add_clicked()
{
    // qDebug() << "inserting row: " << model->insertRow(model->rowCount());
     qDebug() << ui->tabWidget_main->currentIndex();

     //
     switch (ui->tabWidget_main->currentIndex())
     {
     case 0:
          bikes_model->insertRow(bikes_model->rowCount());
         break;
     case 1:
          rental_places_model->insertRow(rental_places_model->rowCount());
         break;
     case 2:
          clients_model->insertRow(clients_model->rowCount());
         break;
     case 3:
        {
         auto t = new FormForAdding(db);
         connect(t, SIGNAL(okClicked(QString, QString, QString, int, int)),
                 this, SLOT(on_addngWidget_ok_clicked(QString, QString, QString, int, int)));
         t->show();
        }
         break;
     case 4:
         bikes_rent_places_model->insertRow(bikes_rent_places_model->rowCount());
         break;
     }
}
void Widget::on_addngWidget_ok_clicked(QString start_date, QString end_date, QString cred_card, int bike_id, int place_id)
{
    QSqlQuery query;
    query.prepare("INSERT INTO rent_agreemnts(start_time, end_time, client_card_number, bike_id, place_id)"
                  "VALUES (STR_TO_DATE(:start_date, '%d/%m/%Y %H:%i:%s'), STR_TO_DATE(:end_date, '%d/%m/%Y %H:%i:%s'),"
                  ":cred_card, :bike_id, :place_id);");
    query.bindValue(":start_date", start_date);
    query.bindValue(":end_date", end_date);
    query.bindValue(":cred_card", cred_card);
    query.bindValue(":bike_id", bike_id);
    query.bindValue(":place_id", place_id);
       query.exec();
       qDebug() << cred_card;
       qDebug() <<  query.lastError().text();
       rent_agreements_model->select();
}


void Widget::on_pushButton_del_clicked()
{
    switch (ui->tabWidget_main->currentIndex())
    {
    case 0:
    {
        int currentIndex = ui->tableView_bikes->currentIndex().row();
        if (currentIndex >= 0)
            qDebug() << "Deleteing row: " << bikes_model->removeRow(currentIndex);
        else
            qDebug() << "No row removed";
        bikes_model->select();
    }
        break;
    case 1:
    {
        int currentIndex = ui->tableView_rent_places->currentIndex().row();
        if (currentIndex >= 0)
            qDebug() << "Deleteing row: " << rental_places_model->removeRow(currentIndex);
        else
            qDebug() << "No row removed";
        rental_places_model->select();
    }

        break;
    case 2:
    {
        int currentIndex = ui->tableView_clients->currentIndex().row();
        if (currentIndex >= 0)
            qDebug() << "Deleteing row: " << clients_model->removeRow(currentIndex);
        else
            qDebug() << "No row removed";
        clients_model->select();
    }
        break;
    case 3:
    {
        int currentIndex = ui->tableView_rent_agreement->currentIndex().row();
        if (currentIndex >= 0)
            qDebug() << "Deleteing row: " << rent_agreements_model->removeRow(currentIndex);
        else
            qDebug() << "No row removed";
        rent_agreements_model->select();
    }
        break;
    case 4:
    {
        int currentIndex = ui->tableView_bike_rent_place->currentIndex().row();
        if (currentIndex >= 0)
            qDebug() << "Deleteing row: " << bikes_rent_places_model->removeRow(currentIndex);
        else
            qDebug() << "No row removed";
        bikes_rent_places_model->select();
    }
        break;
    }
}


void Widget::on_tableView_clients_pressed(const QModelIndex &index)
{
    qDebug() << index.row();
}

void Widget::on_tableView_clients_clicked(const QModelIndex &index)
{
     QString query = "SELECT * FROM rent_agreemnts WHERE client_card_number=";
     qDebug() << index.row();
     query += clients_model->record(index.row()).field(0).value().toString();
     query += ';';
     qDebug() << query;
     clients_additional_model->setQuery(query);
}

void Widget::on_reSelect_clients()
{
    clients_model->select();
}

void Widget::on_pushButton_clicked()
{
    if (ui->tabWidget_main->currentIndex() == 2)
    {
        if (ui->tableView_clients->currentIndex().row() != -1)
        {
            auto index = ui->tableView_clients->currentIndex();
            auto hz = clients_model->record(index.row());
            auto t = new FormForEditing(hz.field(0).value().toString(), hz.field(1).value().toString(), hz.field(2).value().toString(),
                                      hz.field(3).value().toString(), hz.field(4).value().toString(),
                                      hz.field(5).value().toString(), hz.field(6).value().toString());
            connect(t, SIGNAL(updateClientsTable()), this, SLOT(on_reSelect_clients()));
            t->show();
        }

    }
}
