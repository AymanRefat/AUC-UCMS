#include "createcourseview.h"
#include "ui_createcourseview.h"

#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QLayout>
#include <QVBoxLayout>
#include <QSet>
#include "course.h"
#include <QMessageBox>
#include <QWidget>
#include <QMainWindow>
#include "app.h"

extern App *app;

CreateCourseView::CreateCourseView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateCourseView)
{
    ui->setupUi(this);
    load_logout_button(this);
    // Create the input fields
    titleEdit = new QLineEdit(this);
    descriptionEdit = new QLineEdit(this);
    locationEdit = new QLineEdit(this);
    capacityEdit = new QLineEdit(this);
    instructorNameCombobox = new QComboBox(this);
    startDateEdit = new QDateEdit(QDate::currentDate(), this);
    endDateEdit = new QDateEdit(QDate::currentDate(), this);
    startTimeEdit = new QTimeEdit(QTime::currentTime(), this);
    endTimeEdit = new QTimeEdit(QTime::currentTime(), this);
    daysComboBox = new QComboBox(this);
    createButton = new QPushButton("Create Course", this);

    // Populate instructor name combo box
    for (auto &instructor : app->enrollment_manager->get_instructors()) {
        instructorNameCombobox->addItem(instructor.get_name());
    }

    // Populate days combo box
    daysComboBox->addItems({"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"});

    // Create the layout and add widgets
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Title:"));
    layout->addWidget(titleEdit);
    layout->addWidget(new QLabel("Description:"));
    layout->addWidget(descriptionEdit);
    layout->addWidget(new QLabel("Location:"));
    layout->addWidget(locationEdit);
    layout->addWidget(new QLabel("Capacity:"));
    layout->addWidget(capacityEdit);
    layout->addWidget(new QLabel("Instructor Name:"));
    layout->addWidget(instructorNameCombobox);
    layout->addWidget(new QLabel("Start Date:"));
    layout->addWidget(startDateEdit);
    layout->addWidget(new QLabel("End Date:"));
    layout->addWidget(endDateEdit);
    layout->addWidget(new QLabel("Start Time:"));
    layout->addWidget(startTimeEdit);
    layout->addWidget(new QLabel("End Time:"));
    layout->addWidget(endTimeEdit);
    layout->addWidget(new QLabel("Days:"));
    layout->addWidget(daysComboBox);
    layout->addWidget(createButton);

    setLayout(layout);

    // Connect the create button to the slot
    connect(createButton, &QPushButton::clicked, this, [&]() {
        QString title = titleEdit->text();
        QString description = descriptionEdit->text();
        QString location = locationEdit->text();
        int capacity = capacityEdit->text().toInt();
        QUuid id = QUuid::createUuid();
        QString instructor_name = instructorNameCombobox->currentText();
        QDate start_date = startDateEdit->date();
        QDate end_date = endDateEdit->date();
        QTime start_time = startTimeEdit->time();
        QTime end_time = endTimeEdit->time();

        QSet<Day> days;
        QString selectedDay = daysComboBox->currentText();
        if (selectedDay == "Monday") days.insert(Day::Monday);
        else if (selectedDay == "Tuesday") days.insert(Day::Tuesday);
        else if (selectedDay == "Wednesday") days.insert(Day::Wednesday);
        else if (selectedDay == "Thursday") days.insert(Day::Thursday);
        else if (selectedDay == "Friday") days.insert(Day::Friday);
        else if (selectedDay == "Saturday") days.insert(Day::Saturday);
        else if (selectedDay == "Sunday") days.insert(Day::Sunday);
        Course* c   = new Course(title, description, location, capacity, id, app->enrollment_manager->get_instructor(instructor_name).get_id(), start_date, end_date, start_time, end_time, days);
        app->course_manager->create(c);
        QMessageBox::information(this, "Success", "Course created successfully!");
    });
}

CreateCourseView::~CreateCourseView()
{
    delete ui;
}
