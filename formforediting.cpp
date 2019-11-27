#include "formforediting.h"
#include "ui_formforediting.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

FormForEditing::FormForEditing(QString cred_card, QString f_name,
                               QString s_name, QString t_name,
                               QString tel_number, QString gender,
                               QString pass_number, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormForEditing)
{
    ui->setupUi(this);
    if (cred_card.size() != 0 || f_name.size() != 0 || s_name.size() != 0 || t_name.size() != 0
            && tel_number.size() != 0 || gender.size() != 0 || pass_number.size() != 0 )
    {
        ui->lineEdit_cred_card->setReadOnly(true);
    }
    else
        adding = false;
    ui->lineEdit_cred_card->setText(cred_card);

    ui->lineEdit_f_name->setText(f_name);
    ui->lineEdit_s_name->setText(s_name);
    ui->lineEdit_t_name->setText(t_name);
    ui->lineEdit_tel_number->setText(tel_number);
    ui->comboBox_gender->addItem("М");
    ui->comboBox_gender->addItem("Ж");
    ui->comboBox_gender->setCurrentText(gender);
    ui->lineEdit_pass_number->setText(pass_number);
}

FormForEditing::~FormForEditing()
{
    delete ui;
}

void FormForEditing::on_pushButton_clicked()
{
    this->close();
}

void FormForEditing::on_pushButton_2_clicked()
{
    if (adding)
    {
        QSqlQuery query;
        query.prepare("UPDATE clients "
                      "SET "
                           "first_name         = :f_name,"
                           "second_name        = :s_name,"
                           "patronymic         = :t_name,"
                           "phone_number       = :tel_number,"
                           "gender             = :gender,"
                           "passport_number    = :pass_num "
                      "WHERE credit_card_number = :card_number;");
        query.bindValue(":f_name", ui->lineEdit_f_name->text());
        query.bindValue(":s_name", ui->lineEdit_s_name->text());
        query.bindValue(":t_name", ui->lineEdit_t_name->text());
        query.bindValue(":tel_number", ui->lineEdit_tel_number->text());
        query.bindValue(":gender", ui->comboBox_gender->currentText());
        query.bindValue(":pass_num", ui->lineEdit_pass_number->text());
        query.bindValue(":card_number", ui->lineEdit_cred_card->text());
        query.exec();
        qDebug() <<  query.lastError().text();
        emit updateClientsTable();
        this->close();
           //rent_agreements_model->select();
    }
    else
    {
        QSqlQuery query;
        query.prepare("INSERT INTO clients(credit_card_number, first_name, second_name, "
                      "patronymic, phone_number, gender, passport_number)"
                      "VALUES (:credit_card, :f_name,"
                      ":s_name, :t_name, :tel_number, :gender, :pass_num);");
        query.bindValue(":f_name", ui->lineEdit_f_name->text());
        query.bindValue(":s_name", ui->lineEdit_s_name->text());
        query.bindValue(":t_name", ui->lineEdit_t_name->text());
        query.bindValue(":tel_number", ui->lineEdit_tel_number->text());
        query.bindValue(":gender", ui->comboBox_gender->currentText());
        query.bindValue(":pass_num", ui->lineEdit_pass_number->text());
        query.bindValue(":credit_card", ui->lineEdit_cred_card->text());
           query.exec();
           //qDebug() << ;
           qDebug() <<  query.lastError().text();
           emit updateClientsTable();
           QString str = query.lastQuery();
            QMapIterator<QString, QVariant> it(query.boundValues());
            while (it.hasNext())
            {
             it.next();
             str.replace(it.key(),it.value().toString());
            }
            qDebug() <<  str;
    }

}
