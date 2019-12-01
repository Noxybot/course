#include "formforclientsstats.h"
#include "ui_formforclientsstats.h"
#include "QSqlTableModel"
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"
#include "QSqlRecord"
#include "QSqlField"
#include <QDateTime>

FormForClientsStats::FormForClientsStats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormForClientsStats)
{
    ui->setupUi(this);
    m_clients_stat = new QSqlQueryModel;
      m_clients_stat_slave = new QSqlQueryModel;




      ui->tableView_master->setModel(m_clients_stat);
      ui->tableView_slave->setModel(m_clients_stat_slave);
      m_clients_stat->setQuery("select 'У клиента', first_name, second_name, patronymic,"
                               "count(credit_card_number) as 'кол-во', 'договоров' from clients,"
                               "rent_agreemnts where clients.credit_card_number = rent_agreemnts.client_card_number "
                               "group by credit_card_number");

      ui->tableView_master->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
      ui->tableView_slave->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
      ui->tableView_master->setSelectionBehavior(QAbstractItemView::SelectRows);
      ui->tableView_slave->setSelectionBehavior(QAbstractItemView::SelectRows);
}

FormForClientsStats::~FormForClientsStats()
{
    delete ui;
}

void FormForClientsStats::on_tableView_master_clicked(const QModelIndex &index)
{
    ui->tableView_master->clearSelection();
    ui->tableView_master->selectRow(index.row());

    QString query = "SELECT credit_card_number FROM clients WHERE first_name='%1' AND second_name='%2' AND patronymic='%3'";
    query = query.arg(m_clients_stat->record(index.row()).field(1).value().toString(),
                      m_clients_stat->record(index.row()).field(2).value().toString(),
                      m_clients_stat->record(index.row()).field(3).value().toString()
                      );
    query += ';';
    QSqlQuery query1;
    query1.prepare(query);
    query1.exec();
   qDebug() << query1.lastError().text();
   qDebug() << query1.next();
    qDebug() << query1.value(0).toString();
    //qDebug() << index.row();
    QString query3 = "select * from rent_agreemnts where client_card_number='%1'";
    query3 = query3.arg(query1.value(0).toString());


    qDebug() << query3;
    m_clients_stat_slave->setQuery(query3);
}
