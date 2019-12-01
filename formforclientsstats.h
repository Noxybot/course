#ifndef FORMFORCLIENTSSTATS_H
#define FORMFORCLIENTSSTATS_H

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class FormForClientsStats;
}

class FormForClientsStats : public QWidget
{
    Q_OBJECT

public:
    explicit FormForClientsStats(QWidget *parent = nullptr);
    ~FormForClientsStats();

private slots:
    void on_tableView_master_clicked(const QModelIndex &index);

private:
    Ui::FormForClientsStats *ui;
    QSqlQueryModel* m_clients_stat;
    QSqlQueryModel* m_clients_stat_slave;
};

#endif // FORMFORCLIENTSSTATS_H
