#include "formforagrstats.h"
#include "ui_formforagrstats.h"
#include "QSqlTableModel"
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"
#include "QSqlRecord"
#include "QSqlField"
FormForAgrStats::FormForAgrStats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormForAgrStats)
{
    ui->setupUi(this);
    m_agreements = new QSqlQueryModel;
    ui->tableView_agreements->setModel(m_agreements);
    m_bikes = new QSqlQueryModel;
    QSqlQuery query;
    query.prepare("select rent_agreemnts.bike_id, 'Велосипед',"
                  " bikes.model, bikes.mark, bikes.gender, "
                  "'Встречается в ', count(rent_agreemnts.bike_id) as "
                  "'amount', 'договорах' from rent_agreemnts left join bikes on"
                  " rent_agreemnts.bike_id = bikes.bike_id group by rent_agreemnts.bike_id");
    query.exec();
    qDebug() << query.lastError().text();
    m_bikes->setQuery("select rent_agreemnts.bike_id, 'Велосипед',"
                    " bikes.model, bikes.mark, bikes.gender, "
                    "'Встречается в ', count(rent_agreemnts.bike_id) as "
                    "'amount', 'договорах' from rent_agreemnts left join bikes on"
                    " rent_agreemnts.bike_id = bikes.bike_id group by rent_agreemnts.bike_id");
    ui->tableView_stats->setModel(m_bikes);
    ui->tableView_stats->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_agreements->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_stats->setSelectionBehavior(QAbstractItemView::SelectRows);
}

FormForAgrStats::~FormForAgrStats()
{
    delete ui;
}

void FormForAgrStats::on_tableView_stats_clicked(const QModelIndex &index)
{
     ui->tableView_agreements->clearSelection();
     ui->tableView_stats->selectRow(index.row());
     QString query = "SELECT * FROM rent_agreemnts WHERE bike_id=";
     qDebug() << index.row();
     query += m_bikes->record(index.row()).field(0).value().toString();
     query += ';';
     qDebug() << query;
     m_agreements->setQuery(query);
}
