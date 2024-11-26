#include "createeventview.h"
#include "ui_createeventview.h"

#include <QWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QUuid>
#include "app.h"
#include "event.h"

extern App *app;

CreateEventView::CreateEventView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateEventView)
{
    ui->setupUi(this);
    // Initialize widgets
    titleEdit = new QLineEdit(this);
    descriptionEdit = new QLineEdit(this);
    locationEdit = new QLineEdit(this);
    capacityEdit = new QLineEdit(this);
    speakerNameCombobox = new QComboBox(this);
    startDateEdit = new QDateEdit(QDate::currentDate(), this);
    endDateEdit = new QDateEdit(QDate::currentDate(), this);
    startTimeEdit = new QTimeEdit(QTime::currentTime(), this);
    endTimeEdit = new QTimeEdit(QTime::currentTime(), this);
    createButton = new QPushButton("Create Event", this);

    // Populate speaker name combo box
    for (auto &instructor : app->enrollment_manager->get_instructors()) {
        speakerNameCombobox->addItem(instructor.get_name());
    }

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Title:"));
    layout->addWidget(titleEdit);
    layout->addWidget(new QLabel("Description:"));
    layout->addWidget(descriptionEdit);
    layout->addWidget(new QLabel("Location:"));
    layout->addWidget(locationEdit);
    layout->addWidget(new QLabel("Capacity:"));
    layout->addWidget(capacityEdit);
    layout->addWidget(new QLabel("Speaker Name:"));
    layout->addWidget(speakerNameCombobox);
    layout->addWidget(new QLabel("Start Date:"));
    layout->addWidget(startDateEdit);
    layout->addWidget(new QLabel("End Date:"));
    layout->addWidget(endDateEdit);
    layout->addWidget(new QLabel("Start Time:"));
    layout->addWidget(startTimeEdit);
    layout->addWidget(new QLabel("End Time:"));
    layout->addWidget(endTimeEdit);
    layout->addWidget(createButton);

    // Connect the button
    connect(createButton, &QPushButton::clicked, this, [&](){
        Event* event = new Event(
                titleEdit->text(),                  // Title from QLineEdit
                descriptionEdit->text(),            // Description from QLineEdit
                locationEdit->text(),               // Location from QLineEdit
                capacityEdit->text().toInt(),       // Capacity from QLineEdit, converted to int
                QUuid::createUuid(),                // Automatically generates a unique event ID
                app->enrollment_manager->get_instructor(speakerNameCombobox->currentText()).get_id(),
                startDateEdit->date(),              // Start Date from QDateEdit
                endDateEdit->date(),                // End Date from QDateEdit
                startTimeEdit->time(),              // Start Time from QTimeEdit
                endTimeEdit->time()                 // End Time from QTimeEdit
        );
        // debug
        qDebug() << "Event created: " << event->get_title();
        app->event_manager->create(event) ;
    });

    setLayout(layout);
    load_logout_button(this);
};

CreateEventView::~CreateEventView()
{
    delete ui;
}
