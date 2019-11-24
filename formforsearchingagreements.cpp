#include "formforsearchingagreements.h"
#include "ui_formforsearchingagreements.h"
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlQueryModel>
#include <QHeaderView>

FormForSearchingAgreements::FormForSearchingAgreements(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormForSearchingAgreements)
{
    ui->setupUi(this);
    this->setAttribute( Qt::WA_DeleteOnClose );

    QSqlQueryModel *model_client_names = new QSqlQueryModel;
    QTableView *view_clients = new QTableView;
    model_client_names->setQuery("SELECT * FROM clients;");
    ui->comboBox_credit_card->setModel(model_client_names);
    ui->comboBox_credit_card->setView(view_clients);
    view_clients->setColumnHidden(4, true);
    view_clients->setColumnHidden(5, true);
    view_clients->setColumnHidden(6, true);
    view_clients->setSelectionBehavior(QAbstractItemView::SelectRows);
    view_clients->setSelectionMode(QAbstractItemView::SingleSelection);
    view_clients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    QSqlQueryModel *model_bike_names = new QSqlQueryModel;
    QTableView *view_bikes = new QTableView;
    model_bike_names->setQuery("SELECT * FROM bikes;");
    ui->comboBox_bike_id->setModel(model_bike_names);
    ui->comboBox_bike_id->setView(view_bikes);
    view_bikes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view_bikes->setSelectionBehavior(QAbstractItemView::SelectRows);
    view_bikes->setSelectionMode(QAbstractItemView::SingleSelection);


    QSqlQueryModel *model_place_addresses = new QSqlQueryModel;
    QTableView *view_rental_places = new QTableView;
    model_place_addresses->setQuery("SELECT * FROM rental_places;");
    ui->comboBox_rent_place->setModel(model_place_addresses);
    ui->comboBox_rent_place->setView(view_rental_places);
    view_rental_places->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view_rental_places->setSelectionBehavior(QAbstractItemView::SelectRows);
    view_rental_places->setSelectionMode(QAbstractItemView::SingleSelection);
}

AgreementInfo FormForSearchingAgreements::CollectInfo()
{

    return {};
}


FormForSearchingAgreements::~FormForSearchingAgreements()
{
    delete ui;
}

void FormForSearchingAgreements::on_pushButton_clicked()
{
    AgreementInfo info;
    info.id = ui->lineEdit_id->text();
    info.start_time = ui->dateTimeEdit_start->dateTime().toString("yyyy-MM-ddThh:mm:ss.000");
    info.end_time = ui->dateTimeEdit_end->dateTime().toString("yyyy-MM-ddThh:mm:ss.000");
    info.card_number = ui->comboBox_credit_card->currentText();
    info.place_id = ui->comboBox_rent_place->currentText();
    info.bike_id = ui->comboBox_bike_id->currentText();
    emit sendSearchInfo(info);
}

void FormForSearchingAgreements::on_pushButton_2_clicked()
{
    AgreementInfo info;
    info.id = ui->lineEdit_id->text();
    info.start_time = ui->dateTimeEdit_start->dateTime().toString("dd/MM/yyyy hh:mm:ss");
    info.end_time = ui->dateTimeEdit_end->dateTime().toString("dd/MM/yyyy hh:mm:ss");
    info.card_number = ui->comboBox_credit_card->currentText();
    info.place_id = ui->comboBox_rent_place->currentText();
    info.bike_id = ui->comboBox_bike_id->currentText();
    emit sendFilterInfo(info);
}
