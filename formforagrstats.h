#ifndef FORMFORAGRSTATS_H
#define FORMFORAGRSTATS_H

#include <QWidget>
#include "QSqlTableModel"

namespace Ui {
class FormForAgrStats;
}

class FormForAgrStats : public QWidget
{
    Q_OBJECT

public:
    explicit FormForAgrStats(QWidget *parent = nullptr);
    ~FormForAgrStats();

private slots:
    void on_tableView_stats_clicked(const QModelIndex &index);

private:

    QSqlQueryModel* m_bikes;
    QSqlQueryModel* m_agreements;
    Ui::FormForAgrStats *ui;
};

#endif // FORMFORAGRSTATS_H
