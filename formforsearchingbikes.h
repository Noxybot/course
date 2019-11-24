#ifndef FORMFORSEARCHINGBIKES_H
#define FORMFORSEARCHINGBIKES_H

#include <QWidget>
#include "ClientInfo.h"

namespace Ui {
class FormForSearchingBikes;
}

class FormForSearchingBikes : public QWidget
{
    Q_OBJECT

signals:
    void sendBikeSearchInfo(BikeInfo info);
    void sendBikeFilterInfo(BikeInfo info);


public:
    explicit FormForSearchingBikes(QWidget *parent = nullptr);
    ~FormForSearchingBikes();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    BikeInfo CollectInfo();
    Ui::FormForSearchingBikes *ui;
};

#endif // FORMFORSEARCHINGBIKES_H
