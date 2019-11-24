#include "formforsearchingbikes.h"
#include "ui_formforsearchingbikes.h"

FormForSearchingBikes::FormForSearchingBikes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormForSearchingBikes)
{
    ui->setupUi(this);
    ui->comboBox_gender->addItem("М");
    ui->comboBox_gender->addItem("Ж");
     ui->comboBox_gender->addItem("");
     this->setAttribute( Qt::WA_DeleteOnClose );
}

FormForSearchingBikes::~FormForSearchingBikes()
{
    delete ui;
}

void FormForSearchingBikes::on_pushButton_clicked()
{
    emit sendBikeSearchInfo(CollectInfo());
}

BikeInfo FormForSearchingBikes::CollectInfo()
{
    BikeInfo info;
    info.id = ui->lineEdit_b_id->text();
    info.mark = ui->lineEdit_mark->text();
    info.model = ui->lineEdit_model->text();
    info.gender = ui->comboBox_gender->currentText();
    info.amount = ui->lineEdit_amount->text();
    info.pr_for_hour = ui->LineEdit_price->text();
    return  info;
}

void FormForSearchingBikes::on_pushButton_2_clicked()
{
    emit sendBikeFilterInfo(CollectInfo());
}
