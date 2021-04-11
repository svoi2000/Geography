#include "addcountry.h"
#include "ui_addcountry.h"

AddCountry::AddCountry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddCountry)
{
    ui->setupUi(this);
}

AddCountry::~AddCountry()
{
    delete ui;
}

void AddCountry::on_lineEdit_country_textEdited(const QString &arg1)
{
    AddCountry::m_new_country = arg1;
}

void AddCountry::on_lineEdit_capital_textEdited(const QString &arg1)
{
    AddCountry::m_new_capital = arg1;
}

void AddCountry::on_pushButton_add_clicked()
{
    emit add_button_clicked();
}

void AddCountry::on_pushButton_cancel_clicked()
{
    emit cancel_button_clicked();
}

QString AddCountry::get_new_country()
{
    return m_new_country;
}

QString AddCountry::get_new_capital()
{
    return m_new_capital;
}

