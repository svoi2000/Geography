#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    connect(&add_country, SIGNAL(add_button_clicked()),
            this, SLOT(add_new_country()));
    connect(&add_country,SIGNAL(cancel_button_clicked()),
            this, SLOT(show_main_window()));
    connect(&test_knowledge,SIGNAL(cancel_button_clicked()),
            this, SLOT(show_main_window_after_test()));
    connect(&test_knowledge,SIGNAL(answer_button_clicked()),
            this, SLOT(test_of_the_answer()));
    ui->setupUi(this);
    if(!connectDB())
        {
            qDebug() << "Failed to connect DB";
        }

    QSqlQuery query;

    db_input = "CREATE TABLE country_list ( "
               "number INTEGER PRIMARY KEY NOT NULL,"
               "country VARCHAR(20), "
               "capital VARCHAR(20));";

    if(!query.exec(db_input))
    {
          qDebug() << "Cannot create a table" << query.lastError();
    }
}

bool MainWindow::connectDB()
{
    mw_db = QSqlDatabase::addDatabase("QSQLITE");
    mw_db.setDatabaseName("countries");
    if(!mw_db.open())
    {
        qDebug() << "Cannot open database: " << mw_db.lastError();
        return false;
    }
    return true;
}


MainWindow::~MainWindow()
{
    mw_db.removeDatabase("countries");
    delete ui;
}


void MainWindow::on_pushButton_begin_clicked()
{
    number_of_current_country = 1;
    this->hide();
    test_knowledge.show();
    show_next_question();
}

void MainWindow::on_pushButton_add_clicked()
{
    this->hide();
    add_country.show();
}

void MainWindow::add_new_country()
{

    QSqlQuery query;
    QSqlRecord rec;
    m_country = add_country.get_new_country();

    //Проверка того, что в базе уже есть такая страна
    QString str_t = "SELECT EXISTS (SELECT * "
                    "FROM country_list "
                    "WHERE country = '%1' LIMIT 1)";
    db_input = str_t.arg (m_country);
    if(!query.exec(db_input))
    {
        qDebug() << "Unable to check country existing" <<
                    query.lastError() << " : " << query.lastQuery();
        return;
    }
    query.next();
    if (query.value(0).toBool()){
        QMessageBox::critical(0, "Ошибка", "Эта страна уже есть в базе данных");
        return;
    }

    //Добавляем страну в базу данных
    str_t = "SELECT COUNT(*) "
            "FROM country_list;";
    db_input = str_t;
    if(!query.exec(db_input))
    {
        qDebug() << "Unable to get number " << query.lastError() << " : " << query.lastQuery();
        return;
    }
    else
    {
        query.next();
        rec = query.record();
        country_counter = rec.value(0).toInt();
        qDebug() << country_counter;
    }

    m_capital = add_country.get_new_capital();
    ++country_counter;
    str_t = "INSERT INTO country_list(number, country, capital)"
            "VALUES(%1, '%2', '%3');";
    db_input = str_t .arg(country_counter)
                     .arg(m_country)
                     .arg(m_capital);

    if(!query.exec(db_input))
    {
        qDebug() << "Unable to insert data"  << query.lastError() << " : " << query.lastQuery();
    }
    else
    {
        add_country.hide();
        this->show();
    }
}

void MainWindow::show_main_window()
{
    add_country.hide();
    this->show();
}

void MainWindow::show_main_window_after_test()
{
    test_knowledge.hide();
    this->show();
}

void MainWindow::test_of_the_answer()
{
    if (test_knowledge.get_m_asked_capital() == capital_right_answer)
    {
        QMessageBox::information(0, "Правильно", "Столица указана верно");
    } else
        {
            QMessageBox::critical(0, "Ошибка", "Столица указана неверно");
        }
    ++number_of_current_country;
    show_next_question();
}

void MainWindow::show_next_question()
{
    QSqlQuery query;
    QString str_t = "SELECT * "
                    "FROM country_list "
                    "WHERE number = %1;";

    db_input = str_t.arg(number_of_current_country);
    if(!query.exec(db_input))
    {
        qDebug() << "Unable to execute query" <<
                    query.lastError() << " : " << query.lastQuery();
        return;
    }
    QSqlRecord rec = query.record();
    QString country_name;

    if (!query.next())
    {
        QMessageBox::information(0, "Проверка знаний завершена",
                                 "В базе данных закончились страны");
        show_main_window_after_test();
    }

    country_name  = query.value(rec.indexOf("country")).toString();
    test_knowledge.set_country_name(country_name);
    capital_right_answer = query.value(rec.indexOf("capital")).toString();
}
