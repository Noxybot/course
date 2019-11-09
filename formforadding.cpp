#include "formforadding.h"
#include "ui_formforadding.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QHeaderView>
FormForAdding::FormForAdding(QSqlDatabase& _db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormForAdding)
{
    db = &_db;
    ui->setupUi(this);
    ui->dateTimeEdit_start->setMinimumDate(QDate::currentDate());
    ui->dateTimeEdit_start->setDate(QDate::currentDate());
    ui->dateTimeEdit_end->setMinimumDate(QDate::currentDate());
    ui->dateTimeEdit_end->setDate(QDate::currentDate());

    QSqlQueryModel *model_client_names = new QSqlQueryModel;
    QTableView *view_clients = new QTableView;
    model_client_names->setQuery("SELECT * FROM clients;");
    ui->comboBox_cred_card->setModel(model_client_names);
    ui->comboBox_cred_card->setView(view_clients);
    view_clients->setColumnHidden(4, true);
    view_clients->setColumnHidden(5, true);
    view_clients->setColumnHidden(6, true);
    view_clients->setSelectionBehavior(QAbstractItemView::SelectRows);
    view_clients->setSelectionMode(QAbstractItemView::SingleSelection);
    view_clients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    QSqlQueryModel *model_bike_names = new QSqlQueryModel;
    QTableView *view_bikes = new QTableView;
    model_bike_names->setQuery("SELECT * FROM bikes;");
    ui->comboBox_2_bike_id->setModel(model_bike_names);
    ui->comboBox_2_bike_id->setView(view_bikes);
    view_bikes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view_bikes->setSelectionBehavior(QAbstractItemView::SelectRows);
    view_bikes->setSelectionMode(QAbstractItemView::SingleSelection);


    QSqlQueryModel *model_place_addresses = new QSqlQueryModel;
    QTableView *view_rental_places = new QTableView;
    model_place_addresses->setQuery("SELECT * FROM rental_places;");
    ui->comboBox_3_place_id->setModel(model_place_addresses);
    ui->comboBox_3_place_id->setView(view_rental_places);
    view_rental_places->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view_rental_places->setSelectionBehavior(QAbstractItemView::SelectRows);
    view_rental_places->setSelectionMode(QAbstractItemView::SingleSelection);

}

FormForAdding::~FormForAdding()
{
    delete ui;
}

void FormForAdding::on_pushButton_cancel_clicked()
{
    this->close();
}

void FormForAdding::on_pushButton_add_clicked()
{
    emit okClicked(ui->dateTimeEdit_start->dateTime().toString("dd/MM/yyyy hh:mm:ss"), ui->dateTimeEdit_end->dateTime().toString("dd/MM/yyyy hh:mm:ss"),
                   ui->comboBox_cred_card->currentText(), ui->comboBox_2_bike_id->currentText().toInt(),
                   ui->comboBox_3_place_id->currentText().toInt());
    this->close();

}
