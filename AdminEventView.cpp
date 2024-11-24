#include "AdminEventView.h"
#include "ui_AdminEventView.h"

AdminEventView::AdminEventView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminEventView)
{
    ui->setupUi(this);
}

AdminEventView::~AdminEventView()
{
    delete ui;
}
