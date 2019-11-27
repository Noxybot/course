#ifndef FORMFORADDINGBIKES_H
#define FORMFORADDINGBIKES_H

#include <QWidget>
#include "ClientInfo.h"

namespace Ui {
class FormForAddingBikes;
}

class FormForAddingBikes : public QWidget
{
    Q_OBJECT

public:
    explicit FormForAddingBikes(BikeInfo info = {}, QWidget *parent = nullptr);
    ~FormForAddingBikes();

private:
    BikeInfo CollectInfo();

    Ui::FormForAddingBikes *ui;
    bool adding = true;
    QString id ;

signals:
    void OkClicked(BikeInfo info, bool adding);
private slots:
    void on_pushButton_ok_clicked();

};

#endif // FORMFORADDINGBIKES_H
