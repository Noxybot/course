#ifndef FORMFORAGRSTATS2_H
#define FORMFORAGRSTATS2_H

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class FormForAgrStats2;
}

class FormForAgrStats2 : public QWidget
{
    Q_OBJECT

public:
    explicit FormForAgrStats2(QWidget *parent = nullptr);
    ~FormForAgrStats2();

private slots:

    void on_tableView_agrs_by_date_clicked(const QModelIndex &index);

    void on_tableView_expired_slave_clicked(const QModelIndex &index);

    void on_tableView_agrs_expired_clicked(const QModelIndex &index);

private:
    Ui::FormForAgrStats2 *ui;
    QSqlQueryModel* m_agr_date_model;
    QSqlQueryModel* m_agr_date_model_slave;

    QSqlQueryModel* m_agr_exp_model;
    QSqlQueryModel* m_agr_exp_model_slave;


};

#endif // FORMFORAGRSTATS2_H
