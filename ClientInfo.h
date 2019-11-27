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

    bool Empty()
    {
        return id.size() == 0   &&
        mark.size() == 0 &&
        model.size() == 0 &&
        gender.size() == 0 &&
        amount.size() == 0 &&
        pr_for_hour.size() == 0 ;
    }
};
struct AgreementInfo{
    QString id;
    QString start_time;
    QString end_time;
    QString card_number;
    QString bike_id;
    QString place_id;
    QString return_date;
    QString sum;
};

struct RentPlaceInfo
{
    QString id;
    QString address;
    QString f_name;
    QString s_name;
    QString t_name;
    bool Empty()
    {
        return id.size() == 0 &&
        address.size() == 0 &&
        f_name.size() == 0 &&
        s_name.size() == 0 &&
        t_name.size() == 0;
    }
};



#endif // CLIENTINFO_H
