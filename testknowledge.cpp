#include "testknowledge.h"
#include "ui_testknowledge.h"

TestKnowledge::TestKnowledge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestKnowledge)
{
    ui->setupUi(this);
}

TestKnowledge::~TestKnowledge()
{
    delete ui;
}

void TestKnowledge::on_lineEdit_capital_name_textEdited(const QString &arg1)
{
    TestKnowledge::m_asked_capital = arg1;
}

void TestKnowledge::on_pushButton_answer_clicked()
{
    emit answer_button_clicked();
}

void TestKnowledge::on_pushButton_cancel_clicked()
{
    emit cancel_button_clicked();
}

void TestKnowledge::set_country_name(const QString& current_country)
{
    ui->label_country_name->setText(current_country);
    ui->lineEdit_capital_name->setText("");
}

QString TestKnowledge::get_m_asked_capital()
{
    return m_asked_capital;
}
