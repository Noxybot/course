#include "formforaddingrentplace.h"
#include "ui_formforaddingrentplace.h"

FormForAddingRentPlace::FormForAddingRentPlace(RentPlaceInfo info, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormForAddingRentPlace)
{
    ui->setupUi(this);
    if (!info.Empty())
    {
        ui->lineEdit_address->setText(info.address);
        ui->lineEdit_f_name->setText(info.f_name);
        ui->lineEdit_s_name->setText(info.s_name);
        ui->lineEdit_t_name->setText(info.t_name);
        id = info.id;
        adding = false;
    }
}

FormForAddingRentPlace::~FormForAddingRentPlace()
{
    delete ui;
}

RentPlaceInfo FormForAddingRentPlace::CollectInfo()
{
    RentPlaceInfo info;
    info.address = ui->lineEdit_address->text();
    info.f_name = ui->lineEdit_f_name->text();
    info.s_name = ui->lineEdit_s_name->text();
    info.t_name = ui->lineEdit_t_name->text();
    if (!adding)
        info.id = id;
    return info;
}



void FormForAddingRentPlace::on_pushButton_ok_clicked()
{
    emit OkClicked(CollectInfo(), adding);
    if (!adding)
        this->close();
}

void FormForAddingRentPlace::on_pushButton_cancel_clicked()
{
    this->close();
}
