#include "admin_page.h"
#include "ui_admin_page.h"
#include "utils.h"

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
    QPixmap eventsIcon(getCurrentDir() + "/event.png"); // Ensure path is valid
    if (!scheduleIcon.isNull()) {
        int w = ui->label_checkmeeetingsicon->width();
        int h = ui->label_checkmeeetingsicon->height();
        ui->label_checkmeeetingsicon->setPixmap(eventsIcon.scaled(w, h, Qt::KeepAspectRatio));
    } else {
        qDebug() << "Failed to load image: events.png";
    }
}

Admin_page::~Admin_page()
{
    delete ui;
}
