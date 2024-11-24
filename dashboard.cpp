#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    // Pull the courses and events from the app


    // Display them dynamically on the dashboard
}

Dashboard::~Dashboard()
{
    delete ui;
}
