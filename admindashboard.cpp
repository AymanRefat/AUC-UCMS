#include "StudentCourseView.h"
#include "admindashboard.h"
#include "app.h"
#include "course.h"
#include "qpushbutton.h"
#include "ui_admindashboard.h"
#include "utils.h"
#include <QLabel>
#include <QLayout>


extern App *app;

AdminDashboard::AdminDashboard(QWidget *parent)
        : QDialog(parent)
        , ui(new Ui::AdminDashboard)
{
    ui->setupUi(this);
    display();
    load_logout_button(this);
}

void AdminDashboard::display() {
    // Pull the courses and events from the app
    QList<Course*> courses = app->course_manager->get_all();
    QList<Event*> events = app->event_manager->get_all();

    // Display courses and events dyanmically in their frames
    if (frameLayout != nullptr) {
        delete frameLayout;
    }

    frameLayout = new QVBoxLayout(ui->frame_courses);
    for (auto &course : courses) {
        QHBoxLayout *childLayout1 = new QHBoxLayout();
        QHBoxLayout *childLayout2 = new QHBoxLayout();
        QVBoxLayout *childLayout3 = new QVBoxLayout();

        QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        frameLayout->addItem(spacer); // Add a spacer item between the child layouts

        QLabel *firstRow = new QLabel(
                course->get_title() ,
                ui->frame_courses);
        firstRow->setStyleSheet("font-weight: bold;");
        childLayout1->addWidget(firstRow);

        QString s = "Days: ";
        for(auto &day : course->get_days()) {
            s += days[day].left(3) + " ";
        }
        QLabel *secondRow = new QLabel(
                course->get_start_time().toString("hh:mm") + " - " + course->get_end_time().toString("hh:mm") + " - " + s,
                ui->frame_courses);
        childLayout2->addWidget(secondRow);
// Button
        QPushButton *btn = new QPushButton("Delete", ui->frame_courses);
        btn->setObjectName(course->get_id().toString());
        // Handle when button is clicked
        connect(btn, &QPushButton::clicked, [=](){
            app->course_manager->remove(app->course_manager->get(QUuid(btn->objectName())));
            hide();
            AdminDashboard *adminDashboard = new AdminDashboard(this);
            adminDashboard->show();
        });
        childLayout3->addWidget(btn);

        // Add child layouts to the frame's layout
        frameLayout->insertLayout(0, childLayout3);
        frameLayout->insertLayout(0, childLayout2);
        frameLayout->insertLayout(0, childLayout1);

        // Set the layout for the frame (optional if you want to reset it)
    }

    if (frameLayout2 != nullptr) {
        delete frameLayout2;
    }
    frameLayout2 = new QVBoxLayout(ui->frame_events);
    for(auto &event : events) {
        QHBoxLayout *childLayout1 = new QHBoxLayout();
        QHBoxLayout *childLayout2 = new QHBoxLayout();
        QVBoxLayout *childLayout3 = new QVBoxLayout();

        QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        frameLayout2->addItem(spacer); // Add a spacer item between the child layouts

        QLabel *firstRow = new QLabel(
                event->get_title() ,
                ui->frame_events);
        firstRow->setStyleSheet("font-weight: bold;");
        childLayout1->addWidget(firstRow);

        QLabel *secondRow = new QLabel(
                event->get_location() + "  ("  + event->get_start_time().toString("hh:mm") + " - " + event->get_end_time().toString("hh:mm") + ")",
                ui->frame_events);
        childLayout2->addWidget(secondRow);

        // Button
        QPushButton *btn = new QPushButton("Delete", ui->frame_events);
        btn->setObjectName(event->get_id().toString());
        connect(btn, &QPushButton::clicked, [=](){
            app->event_manager->remove(app->event_manager->get(QUuid(btn->objectName())));
            hide();
            AdminDashboard *adminDashboard = new AdminDashboard(this);
            adminDashboard->show();
        });
        childLayout3->addWidget(btn);

        // Add child layouts to the frame's layout
        frameLayout2->insertLayout(0, childLayout3);
        frameLayout2->insertLayout(0, childLayout2);
        frameLayout2->insertLayout(0, childLayout1);

    }


}




AdminDashboard::~AdminDashboard()
{
    delete ui;
    delete frameLayout;
    delete frameLayout2;

}
