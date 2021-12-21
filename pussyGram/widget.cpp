#include "widget.h"
#include "ui_pussyGram.h"
#include "ui_form.h"
#include "chats.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //Chats* model = new Chats(this);
    //ui->chats->setModel(model);

    //список чатов
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setDatabaseName("fn1131_2021");
    m_db.setHostName    ("195.19.32.74");
    m_db.setPort        (5432);
    m_db.setUserName    ("student");
    m_db.setPassword    ("bmstu");
    if (!m_db.open())
        qDebug() << ("Error: " + m_db.lastError().text());
    update_chats_list();
}

Widget::~Widget()
{
    delete ui;
}



void Widget::on_chats_clicked(const QModelIndex &index)
{
    ui->label->setText(ui->chats->currentItem()->text());
}

void Widget::update_chats_list()
{
    QStringList slist;
    //QSqlQuery* qry = new QSqlQuery();
    //qry->prepare();
    ui->chats->clear();
    m_model->setQuery("SELECT chat_name FROM pussy_chats");
}
