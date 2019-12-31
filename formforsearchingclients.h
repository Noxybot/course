#ifndef FORMFORSEARCHINGCLIENTS_H
#define FORMFORSEARCHINGCLIENTS_H

#include <QWidget>
#include <QSqlTableModel>
#include "ClientInfo.h"
namespace Ui {
class FormForSearchingClients;
}

class FormForSearchingClients : public QWidget
{
    Q_OBJECT

public:
    explicit FormForSearchingClients(QWidget *parent = nullptr);
    ~FormForSearchingClients();


signals:
    void sendSearchInfo(ClientInfo info);
    void sendFilterInfo(ClientInfo info);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    ClientInfo CollectInfo();
    Ui::FormForSearchingClients *ui;
    QSqlTableModel* found_clients;
};

#endif // FORMFORSEARCHINGCLIENTS_H
