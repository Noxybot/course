#include "formforsearchingclients.h"
#include "ui_formforsearchingclients.h"

FormForSearchingClients::FormForSearchingClients(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormForSearchingClients)
{
    ui->setupUi(this);
    ui->comboBox_gender->addItem("М");
    ui->comboBox_gender->addItem("Ж");
    ui->comboBox_gender->addItem("");
    this->setAttribute( Qt::WA_DeleteOnClose );
}

FormForSearchingClients::~FormForSearchingClients()
{
    delete ui;
}

 ClientInfo FormForSearchingClients::CollectInfo()
{
    ClientInfo info;
    info.tel = ui->lineEdit_tel->text();
    info.f_name = ui->lineEdit_fname->text();
    info.s_name = ui->lineEdit_sname->text();
    info.t_name = ui->lineEdit_tname->text();
    info.credit_card = ui->lineEdit_credit->text();
    info.passport = ui->LineEdit_passport->text();
    info.gender = ui->comboBox_gender->currentText();
    return info;
}

void FormForSearchingClients::on_pushButton_clicked()
{
    emit sendSearchInfo(CollectInfo());
}

void FormForSearchingClients::on_pushButton_2_clicked()
{
    emit sendFilterInfo(CollectInfo());
}
