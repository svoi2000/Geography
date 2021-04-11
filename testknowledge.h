#ifndef TESTKNOWLEDGE_H
#define TESTKNOWLEDGE_H

#include <QWidget>

namespace Ui {
class TestKnowledge;
}

class TestKnowledge : public QWidget
{
    Q_OBJECT

public:
    explicit TestKnowledge(QWidget *parent = nullptr);
    ~TestKnowledge();

    void set_country_name(const QString& current_country);  //метод автоматического заполнения
                                                            //поля "страна" и стирания поля "столица"
    QString get_m_asked_capital();


signals:
    void cancel_button_clicked();
    void answer_button_clicked();

private slots:
    void on_lineEdit_capital_name_textEdited(const QString &arg1);

    void on_pushButton_answer_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::TestKnowledge *ui;
    QString m_asked_capital;    //поле для пользовательского ввода столицы

};

#endif // TESTKNOWLEDGE_H
