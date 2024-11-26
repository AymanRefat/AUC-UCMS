#include "admin_page.h"
#include "app.h"
#include "ui_admin_page.h"
#include "utils.h"
#include "admineventview.h"
#include "createcourseview.h"
#include "admindashboard.h"

extern App *app;

Admin_page::Admin_page(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Admin_page)
{
    ui->setupUi(this);
    // Set an image to the course icon QLabel
    QPixmap courseIcon(getCurrentDir() + "/learning.png"); // Ensure path is valid
    if (!courseIcon.isNull()) {
        int w = ui->label_managescourseicon->width();
        int h = ui->label_managescourseicon->height();
        ui->label_managescourseicon->setPixmap(courseIcon.scaled(w, h, Qt::KeepAspectRatio));
    } else {
        qDebug() << "Failed to load image: learning.png";
    }

    // Set an image to the schedules icon QLabel
    QPixmap scheduleIcon(getCurrentDir() + "/to-do-list.png"); // Ensure path is valid
    if (!scheduleIcon.isNull()) {
        int w = ui->label_managesregisteration->width();
        int h = ui->label_managesregisteration->height();
        ui->label_managesregisteration->setPixmap(scheduleIcon.scaled(w, h, Qt::KeepAspectRatio));
    } else {
        qDebug() << "Failed to load image: to-do-list.png";
    }

    load_logout_button(this);
}

Admin_page::~Admin_page()
{
    delete ui;
}

void Admin_page::on_pushButton_courses_clicked()
{
    CreateCourseView *adminCourseView = new CreateCourseView(this);
    adminCourseView->show();
}


void Admin_page::on_pushButton_events_clicked()
{
    AdminEventView *adminEventView = new AdminEventView(this);
    adminEventView->show();
}


void Admin_page::on_DeleteBtn_clicked()
{
    AdminDashboard *adminDashboard = new AdminDashboard(this);
    adminDashboard->show();
}

