#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include <QString>
struct ClientInfo{
    QString f_name;
    QString s_name;
    QString t_name;
    QString tel;
    QString gender;
    QString passport;
    QString credit_card;
};
struct BikeInfo{
    QString id;
    QString mark;
    QString model;
    QString gender;
    QString amount;
    QString pr_for_hour;
};
struct AgreementInfo{
    QString id;
    QString start_time;
    QString end_time;
    QString card_number;
    QString bike_id;
    QString place_id;
};

#endif // CLIENTINFO_H
