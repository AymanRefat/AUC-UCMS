#include "StudentCourseView.h"
#include "ui_StudentCourseView.h"

StudentCourseView::StudentCourseView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StudentCourseView)
{
    ui->setupUi(this);
}

StudentCourseView::~StudentCourseView()
{
    delete ui;
}
