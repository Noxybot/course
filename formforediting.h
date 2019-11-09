#ifndef FORMFOREDITING_H
#define FORMFOREDITING_H

#include <QWidget>
#include <QString>
namespace Ui {
class FormForEditing;
}

class FormForEditing : public QWidget
{
    Q_OBJECT

public:
    explicit FormForEditing(QString cred_card, QString f_name,
                            QString s_name, QString t_name,
                            QString tel_number, QString gender,
                            QString pass_number, QWidget *parent = nullptr);
    ~FormForEditing();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void updateClientsTable();

private:
    Ui::FormForEditing *ui;
};

#endif // FORMFOREDITING_H
