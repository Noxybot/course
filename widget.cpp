#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>
#include <QMessageBox>

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

    ui->tableView_bikes->setSortingEnabled(true);
    ui->tableView_rent_places->setSortingEnabled(true);
    ui->tableView_additional_clients->setSortingEnabled(true);
    ui->tableView_clients->setSortingEnabled(true);
    ui->tableView_rent_agreement->setSortingEnabled(true);
    ui->tableView_bike_rent_place->setSortingEnabled(true);

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

    ui->tableView_clients->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tableView_bikes->setSelectionMode(QAbstractItemView::MultiSelection);

    ui->tableView_bikes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_rent_places->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_clients->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_additional_clients->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_rent_agreement->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_bike_rent_place->setSelectionBehavior(QAbstractItemView::SelectRows);

}

void Widget::on_pushButton_execute_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(ui->textEdit_query->toPlainText());
    ui->tableView_custom_query->setModel(model);
    ui->tableView_custom_query->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    auto reply = QMessageBox::question(this, "Удаление", "Удалить?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
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
      } else {
        qDebug() << "Yes was *not* clicked";
      }



}


void Widget::on_tableView_clients_pressed(const QModelIndex &index)
{
    qDebug() << index.row();
}

void Widget::on_tableView_clients_clicked(const QModelIndex &index)
{
    ui->tableView_clients->clearSelection();
     ui->tableView_clients->selectRow(index.row());
     QString query = "SELECT * FROM rent_agreemnts WHERE client_card_number=";
     qDebug() << index.row();
     query += clients_model->record(index.row()).field(0).value().toString();
     query += ';';
     qDebug() << query;
     clients_additional_model->setQuery(query);
}

void Widget::on_reSelect_clients()
{
    qDebug() << "HGHDFGDF";
    clients_model->setFilter("");
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

static bool CompareStiring(const QString& first, const QString& second)
{
    if (second.size() == 0)
        return true;
    return first == second;
}
static QString ExVal(const QSqlRecord& rec, const QString& first)
{
    return rec.field(first).value().toString();
}

void Widget::FindClients(ClientInfo info)
{
    std::size_t row_count = clients_model->rowCount();
    ui->tableView_clients->clearSelection();
    clients_additional_model->clear();
    clients_model->setFilter("");
    clients_model->select();
    int selected_count = 0;
    int last = 0;
    for ( std::size_t i = 0; i < row_count; ++i)
    {
        auto row = clients_model->record(i);
        if (CompareStiring(ExVal(row, "credit_card_number"), info.credit_card) &&
            CompareStiring(ExVal(row, "first_name"), info.f_name) &&
            CompareStiring(ExVal(row, "second_name"), info.s_name) &&
            CompareStiring(ExVal(row, "patronymic"), info.t_name) &&
            CompareStiring(ExVal(row, "phone_number"), info.tel) &&
            CompareStiring(ExVal(row, "gender"), info.gender) &&
            CompareStiring(ExVal(row, "passport_number"), info.passport))
        {
            ++selected_count;
            last = i;
            ui->tableView_clients->selectRow(i);
        }

    }
    if (selected_count == 1)
        on_tableView_clients_clicked(clients_model->index(last, 0));
}

static void AddParamToFilter(QString &filter, QString param_name, QString param_val)
{
    if (param_val.size() != 0)
    {
        filter += param_name;
        filter += " LIKE '%";
        filter += param_val;
        filter += "%' AND ";
    }
}
//static void AddParamToFilter(QString &filter, QString param_name, int param_val)
//{
//    if (param_val.size() != 0)
//    {
//        filter += param_name;
//        filter += " LIKE '%";
//        filter += param_val;
//        filter += "%' AND ";
//    }
//}

void Widget::FilterClients(ClientInfo info)
{
    ui->tableView_clients->clearSelection();
    clients_additional_model->clear();
    QString filter;
    AddParamToFilter(filter, "credit_card_number", info.credit_card);
    AddParamToFilter(filter, "first_name", info.f_name);
    AddParamToFilter(filter, "second_name", info.s_name);
    AddParamToFilter(filter, "patronymic", info.t_name);
    AddParamToFilter(filter, "phone_number", info.tel);
    AddParamToFilter(filter, "gender", info.gender);
    AddParamToFilter(filter, "passport_number", info.passport);
    filter.resize(filter.size() - 4);
    qDebug() << filter;
    clients_model->setFilter(filter);
    if (clients_model->rowCount() == 1)
        on_tableView_clients_clicked(clients_model->index(0, 0));

}


void Widget::FindBikes(BikeInfo info)
{
    std::size_t row_count = bikes_model->rowCount();
    ui->tableView_bikes->clearSelection();
    bikes_model->setFilter("");
    bikes_model->select();
    int selected_count = 0;
    int last = 0;
    for ( std::size_t i = 0; i < row_count; ++i)
    {
        auto row = bikes_model->record(i);
        if (CompareStiring(ExVal(row, "bike_id"), info.id) &&
            CompareStiring(ExVal(row, "mark"), info.mark) &&
            CompareStiring(ExVal(row, "model"), info.model) &&
            CompareStiring(ExVal(row, "gender"), info.gender) &&
            CompareStiring(ExVal(row, "amount"), info.amount) &&
            CompareStiring(ExVal(row, "price_for_an_four"), info.pr_for_hour))
        {
            ++selected_count;
            last = i;
            ui->tableView_bikes->selectRow(i);
        }

   }
}

void  Widget::FilterBikes(BikeInfo info)
{
    ui->tableView_bikes->clearSelection();
    QString filter;
    AddParamToFilter(filter, "bike_id", info.id);
    AddParamToFilter(filter, "mark", info.mark);
    AddParamToFilter(filter, "model", info.model);
    AddParamToFilter(filter, "gender", info.gender);
    AddParamToFilter(filter, "amount", info.amount);
    AddParamToFilter(filter, "price_for_an_four", info.pr_for_hour);
    filter.resize(filter.size() - 4);
    qDebug() << filter;
    bikes_model->setFilter(filter);
}



void Widget::on_tableView_bikes_clicked(const QModelIndex &index)
{
    ui->tableView_bikes->clearSelection();
    ui->tableView_bikes->selectRow(index.row());
}
void Widget::on_tableView_rent_agreement_clicked(const QModelIndex &index)
{
    ui->tableView_rent_agreement->clearSelection();
    ui->tableView_rent_agreement->selectRow(index.row());
}

void  Widget::FindAgreements(AgreementInfo info)
{
    std::size_t row_count = rent_agreements_model->rowCount();
    ui->tableView_rent_agreement->clearSelection();
    rent_agreements_model->setFilter("");
    rent_agreements_model->select();
    int selected_count = 0;
    int last = 0;
    for ( std::size_t i = 0; i < row_count; ++i)
    {
        auto row = rent_agreements_model->record(i);
        if (CompareStiring(ExVal(row, "agreement_id"), info.id) &&
            CompareStiring(ExVal(row, "start_time"), info.start_time) &&
            CompareStiring(ExVal(row, "end_time"), info.end_time) &&
            CompareStiring(ExVal(row, "client_card_number"), info.card_number) &&
            CompareStiring(ExVal(row, "bike_id"), info.bike_id) &&
            CompareStiring(ExVal(row, "place_id"), info.place_id))
        {
            ++selected_count;
            last = i;
            ui->tableView_rent_agreement->selectRow(i);
        }

   }
}
void  Widget::FilterAgreements(AgreementInfo info)
{
    ui->tableView_rent_agreement->clearSelection();
    QString filter;
    AddParamToFilter(filter, "agreement_id", info.id);
    if (info.start_time.size() != 0 && info.end_time.size() != 0)
    {
        filter += "start_time=";
        filter += QString("STR_TO_DATE(%1, '%d/%m/%Y %H:%i:%s')").arg(info.start_time);
        filter += " AND end_time=";
        filter += QString("STR_TO_DATE(%1, '%d/%m/%Y %H:%i:%s') AND ").arg(info.end_time);
        filter += " AND ";
    }
    else if (info.start_time.size() != 0 && info.end_time.size() == 0)
    {
        filter += "start_time=";
        filter += QString("STR_TO_DATE(%1, '%d/%m/%Y %H:%i:%s')").arg(info.start_time);
        filter += " AND ";
    }
    else
    {
        filter += "end_time=";
        filter += QString("STR_TO_DATE(%1, '%d/%m/%Y %H:%i:%s') AND ").arg(info.end_time);
        filter += " AND ";
    }


    AddParamToFilter(filter, "client_card_number", info.card_number);
    AddParamToFilter(filter, "bike_id", info.bike_id);
    AddParamToFilter(filter, "place_id", info.place_id);
    filter.resize(filter.size() - 4);
    qDebug() << filter;
    rent_agreements_model->setFilter(filter);

}


