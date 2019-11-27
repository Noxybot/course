#include "formforaddingbikes.h"
#include "ui_formforaddingbikes.h"

FormForAddingBikes::FormForAddingBikes(BikeInfo info,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormForAddingBikes)
{
    ui->setupUi(this);
    ui->comboBox_gender->addItem("М");
    ui->comboBox_gender->addItem("Ж");
    ui->comboBox_gender->addItem("");
    this->setAttribute( Qt::WA_DeleteOnClose );
    if (!info.Empty())
    {
        ui->lineEdit_mark->setText(info.mark);
        ui->lineEdit_model->setText(info.model);
        ui->comboBox_gender->setCurrentText(info.gender);
        ui->spinBox_amount->setValue(info.amount.toInt());
        ui->spinBox_price->setValue(info.pr_for_hour.toInt());
        adding = false;
        id = info.id;
    }


}
BikeInfo FormForAddingBikes::CollectInfo()
{
    BikeInfo info;
    info.mark = ui->lineEdit_mark->text();
    info.model = ui->lineEdit_model->text();
    info.gender = ui->comboBox_gender->currentText();
    info.amount = ui->spinBox_amount->text();
    info.pr_for_hour = ui->spinBox_price->text();
    if (!adding)
        info.id = id;
    return  info;
}

FormForAddingBikes::~FormForAddingBikes()
{
    delete ui;
}

void FormForAddingBikes::on_pushButton_ok_clicked()
{
    emit OkClicked(CollectInfo(), adding);
    if (!adding)
        this->close();
}
