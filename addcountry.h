#ifndef ADDCOUNTRY_H
#define ADDCOUNTRY_H

#include <QWidget>

namespace Ui {
class AddCountry;
}

class AddCountry : public QWidget
{
    Q_OBJECT

public:
    explicit AddCountry(QWidget *parent = nullptr);
    ~AddCountry();

    QString get_new_country();
    QString get_new_capital();

signals:
    void add_button_clicked();
    void cancel_button_clicked();

private slots:
    void on_lineEdit_country_textEdited(const QString &arg1);

    void on_lineEdit_capital_textEdited(const QString &arg1);

    void on_pushButton_add_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::AddCountry *ui;
    QString m_new_country;  //поля для пользовательского ввода страны
    QString m_new_capital;  //и столицы
};

#endif // ADDCOUNTRY_H
