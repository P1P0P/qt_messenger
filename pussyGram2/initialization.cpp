#include "initialization.h"
#include "ui_initialization.h"

initialization::initialization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::initialization)
{
    ui->setupUi(this);
    ui->sign_up_widget->hide();
    setFixedSize(500, 300);

    //логины
    local_db = QSqlDatabase::addDatabase("QSQLITE");
    local_db.setDatabaseName("db_password");
    local_db.open();

    QSqlQuery query(local_db);
    query.exec("CREATE TABLE passwords(login TEXT, password TEXT)");

    QStringList list;
    query.exec("SELECT login FROM passwords");
    while (query.next()){
        qDebug() << query.value(0).toString();
        list << query.value(0).toString();
    }
    ui->login_box->addItems(list);
}

initialization::~initialization()
{
    delete ui;
}


void initialization::on_reg_button_clicked()
{
    ui->sign_in_widget->hide();
    ui->sign_up_widget->show();
}


void initialization::on_log_button_clicked()
{
    ui->sign_up_widget->hide();
    ui->sign_in_widget->show();
}




void initialization::on_login_box_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query(local_db);
    query.exec("SELECT password FROM passwords WHERE login = '" + arg1 + "'");
    //query.exec("SELECT login FROM passwords LIMIT 1");
    qDebug() << query.value(0).toString();
    ui->password_line->setText(query.value(0).toString());
}

