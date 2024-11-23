#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);

    // Set an image to the course icon QLabel
    QPixmap courseIcon("E:\\Picture\\learning.png"); // Ensure path is valid
    if (!courseIcon.isNull()) {
        int w = ui->label_courseicon->width();
        int h = ui->label_courseicon->height();
        ui->label_courseicon->setPixmap(courseIcon.scaled(w, h, Qt::KeepAspectRatio));
    } else {
        qDebug() << "Failed to load image: learning.png";
    }

    // Set an image to the schedules icon QLabel
    QPixmap scheduleIcon("C:\\Users\\HP\\Downloads\\to-do-list.png"); // Ensure path is valid
    if (!scheduleIcon.isNull()) {
        int w = ui->label_schedulesicon->width();
        int h = ui->label_schedulesicon->height();
        ui->label_schedulesicon->setPixmap(scheduleIcon.scaled(w, h, Qt::KeepAspectRatio));
    } else {
        qDebug() << "Failed to load image: to-do-list.png";
    }
    QPixmap eventsIcon("C:\\Users\\HP\\Downloads\\event.png"); // Ensure path is valid
    if (!scheduleIcon.isNull()) {
        int w = ui->label_eventsicon->width();
        int h = ui->label_eventsicon->height();
        ui->label_eventsicon->setPixmap(eventsIcon.scaled(w, h, Qt::KeepAspectRatio));
    } else {
        qDebug() << "Failed to load image: events.png";
    }
}

Dashboard::~Dashboard()
{
    delete ui;
}
