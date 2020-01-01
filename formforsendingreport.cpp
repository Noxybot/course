#include "formforsendingreport.h"
#include "ui_formforsendingreport.h"
#include "src/SmtpMime"
#include <QSqlQueryModel>

FormForSendingReport::FormForSendingReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormForSendingReport)
{
    ui->setupUi(this);
}

FormForSendingReport::~FormForSendingReport()
{
    delete ui;
}

void FormForSendingReport::on_pushButton_clicked()
{
    auto email = ui->lineEdit->text();
    // This is a first demo application of the SmtpClient for Qt project

        // First we need to create an SmtpClient object
        // We will use the Gmail's smtp server (smtp.gmail.com, port 465, ssl)

        SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

        // We need to set the username (your email address) and the password
        // for smtp authentification.

        smtp.setUser("eduard.voronkin@nure.ua");
        smtp.setPassword("Andyou33");

        // Now we create a MimeMessage object. This will be the email.

        MimeMessage message;

        message.setSender(new EmailAddress("eduard.voronkin@nure.ua", "Eduard Voronkin"));
        message.addRecipient(new EmailAddress(email, ""));
        message.setSubject("Отчет за месяц");

        // Now add some text to the email.
        // First we create a MimeText object.
        QString strStream;
        QTextStream out(&strStream);
        QString title = "Отчет за месяц";
        QDate date = QDate::currentDate();
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("select * from rent_agreemnts;");
        const int rowCount = model->rowCount();
        const int columnCount = model->columnCount();

        out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg(title)
            <<  "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"
             << QString("<p align=center><span style=font-size:20.25pt;>%1</span></p>\n").arg(title)
                << QString("<p align=center><span style=font-size:20.25pt;>%1</span></p>\n").arg(date.toString())
            <<"<table border=1 cellspacing=0 cellpadding=1 width=100%>\n";

        out << "<thead><tr bgcolor=#f0f0f0>";
        for (int column = 0; column < columnCount; column++)
                out << QString("<th>%1</th>").arg(model->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++) {
            out << "<tr>";
            for (int column = 0; column < columnCount; column++) {
                    QString data = model->data(model->index(row, column)).toString().simplified();
                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
            out << "</tr>\n";
        }
        out <<  "</table>\n"
            "</body>\n"
            "</html>\n";

       // QTextDocument *document = new QTextDocument();
       // document->setHtml(strStream);
        //qDebug() << strStream;
        qDebug() << email;

        MimeHtml text;

        text.setHtml(strStream);

        // Now add it to the mail

        message.addPart(&text);

        // Now we can send the mail

        if (!smtp.connectToHost()) {
        qDebug() << "Failed to connect to host!" << endl;
        //return -1;
    }

    if (!smtp.login()) {
        qDebug() << "Failed to login!" << endl;
       // return -2;
    }

    if (!smtp.sendMail(message)) {
        qDebug() << "Failed to send mail!" << endl;
        //return -3;
    }
        smtp.quit();



}
