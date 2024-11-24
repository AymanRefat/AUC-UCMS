#include "StudentEventView.h"
#include "ui_StudentEventView.h"

StudentEventView::StudentEventView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StudentEventView)
{
    ui->setupUi(this);
}

StudentEventView::~StudentEventView()
{
    delete ui;
}
