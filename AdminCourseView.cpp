#include "AdminCourseView.h"
#include "ui_AdminCourseView.h"

AdminCourseView::AdminCourseView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminCourseView)
{
    ui->setupUi(this);
}

AdminCourseView::~AdminCourseView()
{
    delete ui;
}
