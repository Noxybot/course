#include "formforagrstats2.h"
#include "ui_formforagrstats2.h"
#include "QSqlTableModel"
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"
#include "QSqlRecord"
#include "QSqlField"
#include <QDateTime>

FormForAgrStats2::FormForAgrStats2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormForAgrStats2)
{
    ui->setupUi(this);

    m_agr_date_model_slave = new QSqlQueryModel;
    m_agr_exp_model_slave = new QSqlQueryModel;
    ui->tableView_by_date_slave->setModel(m_agr_date_model_slave);
    ui->tableView_expired_slave->setModel(m_agr_exp_model_slave);

    m_agr_date_model = new QSqlQueryModel;
    m_agr_exp_model = new QSqlQueryModel;

    ui->tableView_agrs_by_date->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_agrs_expired->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_by_date_slave->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_expired_slave->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QSqlQuery query;
    query.prepare("select 'В день с датой', start_time, 'оформлен(о)', count(start_time), 'договор(ов)' from rent_agreemnts "
                   "group by start_time");
    m_agr_date_model->setQuery("select 'В день с датой', date(start_time), 'оформлен(о)', count(date(start_time)), 'договор(ов)' from rent_agreemnts "
                               "group by date(start_time)");
    m_agr_exp_model->setQuery("select 'В день с датой', date(start_time), 'просрочено', count(start_time), 'договоров' from rent_agreemnts "
                              "where end_time < return_date "
                              "group by date(start_time)");
    ui->tableView_agrs_by_date->setModel(m_agr_date_model);
    ui->tableView_agrs_expired->setModel(m_agr_exp_model);
    query.exec();
    qDebug() << query.lastError().text();


    ui->tableView_agrs_by_date->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_agrs_expired->setSelectionBehavior(QAbstractItemView::SelectRows);
}

FormForAgrStats2::~FormForAgrStats2()
{
    delete ui;
}


void FormForAgrStats2::on_tableView_agrs_by_date_clicked(const QModelIndex &index)
{
     //QString("STR_TO_DATE(%1, '%d/%m/%Y %H:%i:%s') AND ").arg(info.return_date);
    ui->tableView_agrs_by_date->clearSelection();
    ui->tableView_agrs_by_date->selectRow(index.row());
    QString query = "SELECT * FROM rent_agreemnts WHERE date(start_time)=date(STR_TO_DATE('%1', '%Y-%m-%d %H:%i:%s'))";
    qDebug() << index.row();
    qDebug() << m_agr_date_model->record(index.row()).field(1).value().toDateTime();
    query = query.arg(m_agr_date_model->record(index.row()).field(1).value().toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query += ';';
    qDebug() << query;
    QSqlQuery query1;
    query1.prepare(query);
    query1.exec();
    qDebug() << query1.lastError().text();

    m_agr_date_model_slave->setQuery(query);
}

void FormForAgrStats2::on_tableView_expired_slave_clicked(const QModelIndex &index)
{

}

void FormForAgrStats2::on_tableView_agrs_expired_clicked(const QModelIndex &index)
{
    //QString("STR_TO_DATE(%1, '%d/%m/%Y %H:%i:%s') AND ").arg(info.return_date);
   ui->tableView_agrs_expired->clearSelection();
   ui->tableView_agrs_expired->selectRow(index.row());
   QString query = "SELECT * FROM rent_agreemnts WHERE end_time < return_date AND date(start_time)=date(STR_TO_DATE('%1', '%Y-%m-%d %H:%i:%s')) ";
   qDebug() << index.row();
   qDebug() << m_agr_exp_model->record(index.row()).field(1).value().toDateTime();
  query = query.arg(m_agr_exp_model->record(index.row()).field(1).value().toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
   query += ';';
   qDebug() << query;
   QSqlQuery query1;
   query1.prepare(query);
   query1.exec();
   qDebug() << query1.lastError().text();

   m_agr_exp_model_slave->setQuery(query);
}
