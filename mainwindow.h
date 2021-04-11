#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QtSql>
#include "addcountry.h"
#include "testknowledge.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool connectDB(); // прототип метода подключения к БД
    void show_next_question();  //прототип метода вопроса о столице следующей страны

private slots:
    void on_pushButton_begin_clicked(); //прототип слота - начало проверки знаний

    void on_pushButton_add_clicked();

    void add_new_country(); //прототип слота добавления страны

    void show_main_window();

    void show_main_window_after_test();

    void test_of_the_answer();  //прототип проверки столицы, введенной пользователем


private:
    Ui::MainWindow *ui;

    AddCountry add_country; // экземпляры окна добавления страны и окна проверки знаний
    TestKnowledge test_knowledge; // принадлежат главному окну

    QString m_country; // строки для обработки
    QString m_capital; // пользовательского ввода

    QString capital_right_answer;   //столица - правильный ответ

    QString db_input; // строка для отправки запроса к БД

    QSqlDatabase mw_db; // экземпляр подключения к БД

    int country_counter;  //счетчик стран для добавления новой страны
    int number_of_current_country;  //счетчик текущей страны в процессе проверки знаний



};
#endif // MAINWINDOW_H
