#ifndef FORMFORSENDINGREPORT_H
#define FORMFORSENDINGREPORT_H

#include <QWidget>

namespace Ui {
class FormForSendingReport;
}

class FormForSendingReport : public QWidget
{
    Q_OBJECT

public:
    explicit FormForSendingReport(QWidget *parent = nullptr);
    ~FormForSendingReport();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FormForSendingReport *ui;
};

#endif // FORMFORSENDINGREPORT_H
