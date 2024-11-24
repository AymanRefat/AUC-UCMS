#include "admin_page.h"
#include "ui_admin_page.h"

Admin_page::Admin_page(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Admin_page)
{
    ui->setupUi(this);
}

Admin_page::~Admin_page()
{
    delete ui;
}
