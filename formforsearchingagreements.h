#ifndef FORMFORSEARCHINGAGREEMENTS_H
#define FORMFORSEARCHINGAGREEMENTS_H

#include <QWidget>
#include "ClientInfo.h"

namespace Ui {
class FormForSearchingAgreements;
}

class FormForSearchingAgreements : public QWidget
{
    Q_OBJECT

public:
    explicit FormForSearchingAgreements(QWidget *parent = nullptr);
    ~FormForSearchingAgreements();

signals:
    void sendSearchInfo(AgreementInfo info);
    void sendFilterInfo(AgreementInfo info);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    AgreementInfo CollectInfo();
    Ui::FormForSearchingAgreements *ui;
};

#endif // FORMFORSEARCHINGAGREEMENTS_H
