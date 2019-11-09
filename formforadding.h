#ifndef FORMFORADDING_H
#define FORMFORADDING_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class FormForAdding;
}

class FormForAdding : public QWidget
{
    Q_OBJECT

public:
    explicit FormForAdding(QSqlDatabase& _db, QWidget *parent = nullptr);
    ~FormForAdding();

signals:
    void okClicked(QString start_date, QString end_date, QString cred_card, int bike_id, int place_id);


private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_add_clicked();



private:
    Ui::FormForAdding *ui;
    QSqlDatabase *db;
    QSqlQuery *clients_names;
    QSqlQuery *bikes_names;
    QSqlQuery *places_addres;

};

#endif // FORMFORADDING_H
