#ifndef FORMFORADDINGRENTPLACE_H
#define FORMFORADDINGRENTPLACE_H

#include <QWidget>
#include "ClientInfo.h"

namespace Ui {
class FormForAddingRentPlace;
}

class FormForAddingRentPlace : public QWidget
{
    Q_OBJECT

public:
    explicit FormForAddingRentPlace(RentPlaceInfo info = {},  QWidget *parent = nullptr);
    ~FormForAddingRentPlace();
    bool adding = true;

private:
    RentPlaceInfo CollectInfo();
    Ui::FormForAddingRentPlace *ui;
    QString id;
signals:
    void OkClicked(RentPlaceInfo info, bool adding);
private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_cancel_clicked();
};

#endif // FORMFORADDINGRENTPLACE_H
