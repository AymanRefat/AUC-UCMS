#include "activityrepository.h"
#include "course.h"
#include "utils.h"
#include "event.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QSet>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>

ActivityRepository::ActivityRepository(ActivityType type, QString filename) {

    // Setting the filename and type
    this->filename = filename;
    this->type = type;

    // Initializing the container
    container = QHash<QUuid, Activity*>();

}

ActivityRepository::~ActivityRepository() {
    // Freeing the memory
    for (auto &activity : container)
        delete activity;
}

void ActivityRepository::load() {

    // Open file in resource file
    QFile file(getCurrentDir() + "/" + filename);

    // Check if file is open
    if (!file.open(QIODevice::ReadOnly))
        throw std::runtime_error(("Could not open file: " + file.fileName() + ", Error: " + file.errorString()).toStdString());

    // Read file
    QTextStream in(&file);

    // Skip the title (Just for now. The title will be deleted in the end)
    in.readLine();

    // Read the data
    while (!in.atEnd()) {
        // Read the row and split it
        QStringList row = parseCsvLine(in.readLine());

        // Activity object to store data
        Activity* activity;

        // Constructing the time
        QStringList start_time_ist = row[ActivityDataRow::StartTime].split(" ");
        QStringList end_time_list = row[ActivityDataRow::EndTime].split(" ");

        QTime start_time = QTime(start_time_ist[0].toInt(), end_time_list[1].toInt());
        QTime end_time = QTime(end_time_list[0].toInt(), end_time_list[1].toInt());

        // Constructing the date
        QStringList start_date_list = row[ActivityDataRow::StartDate].split(" ");
        QStringList end_date_list = row[ActivityDataRow::EndDate].split(" ");

        QDate start_date = QDate(start_date_list[0].toInt(), start_date_list[1].toInt(), start_date_list[2].toInt());
        QDate end_date = QDate(end_date_list[0].toInt(), end_date_list[1].toInt(), end_date_list[2].toInt());

        // Constructing the activity object
        if (type == ActivityType::CourseType) {

            // Constructing days
            QStringList days_list = row[CourseDataRow::Days].split(" ");
            QSet<Day> days;
            for(QString &day : days_list)
                days.insert(static_cast<Day>(day.toInt()));

            // Course Object
            activity = new class Course(
                row[ActivityDataRow::Title], row[ActivityDataRow::Description], row[ActivityDataRow::Location],
                row[ActivityDataRow::Capacity].toInt(), QUuid(row[ActivityDataRow::Id]), QUuid(row[CourseDataRow::InstructorId]),
                start_date, end_date,
                start_time, end_time, days
            );

        } else {

            // Event Object
            activity = new class Event(
                row[ActivityDataRow::Title], row[ActivityDataRow::Description], row[ActivityDataRow::Location],
                row[ActivityDataRow::Capacity].toInt(), QUuid(row[ActivityDataRow::Id]), QUuid(row[EventDataRow::SpeakerId]),
                start_date, end_date, start_time, end_time
                );
        }

        // Add to container
        container.insert(activity->get_id(), activity);
    }

    // Closing the file
    file.close();
}

void ActivityRepository::store() {

    // Open file
    QFile file(getCurrentDir() + "/" + filename);

    // Check if file is open
    if (!file.open(QIODevice::ReadWrite))
        throw std::runtime_error(("Could not open file: " + file.fileName() + ", Error: " + file.errorString()).toStdString());

    // Write to file
    QTextStream out(&file);


    // Write the title (Just for now. The title should be deleted in the end)
    if (type == ActivityType::CourseType)
        out << "id,title,description,capacity,location,start_date,end_date,days,start_time,end_time,instructor_id\n";
    else
        out << "id,title,description,capacity,location,date_time\n";

    // Write the data
    for (auto &activity : container) {
        if (type == ActivityType::CourseType) {

            // Dynamic Casting to a Course object
            class Course *course = dynamic_cast<class Course*>(activity);

            // Writing to the file
            out << course->get_id().toString() << ","
                << '"' << course->get_title() << '"' << ","
                << '"' << course->get_description() << '"' << ","
                << course->get_capacity() << ","
                << '"' << course->get_location() << '"' << ","
                << course->get_start_date().toString("yyyy MM dd") << ","
                << course->get_end_date().toString("yyyy MM dd") << ","
                << course->get_start_time().toString("hh mm") << ","
                << course->get_end_time().toString("hh mm") << ","
                << course->get_instructor_id().toString() << ",";
                QSet<Day> days = course->get_days();
                for(auto &day : days)
                    out << day << " ";
                out << "\n";

        } else {
            class Event* event = dynamic_cast<class Event*>(activity);
            out << event->get_id().toString() << ","
                << '"' <<  event->get_title() << '"' << ","
                << '"' << event->get_description() << '"' << ","
                << event->get_capacity() << ","
                << '"' << event->get_location() << '"' << ","
                << event->get_start_date().toString("yyyy MM dd") << ","
                << event->get_end_date().toString("yyyy MM dd") << ","
                << event->get_start_time().toString("hh mm") << ","
                << event->get_end_time().toString("hh mm") << ","
                << event->get_speaker_id().toString() << "\n";
        }
    }

    // Closing the file
    file.close();
}


void ActivityRepository::add(Activity* activity) {
    container.insert(activity->get_id(), activity);
}

void ActivityRepository::remove(Activity* activity) {
    remove(activity->get_id());
}

void ActivityRepository::remove(QUuid id) {
    if (!container.contains(id))
        throw std::runtime_error("Activity not found");
    container.remove(id);
}

void ActivityRepository::update(Activity* activity) {
    container.insert(activity->get_id(), activity);
}

Activity* ActivityRepository::get(QUuid id) {
    if (!container.contains(id))
        throw std::runtime_error("Activity not found");

    return container.value(id);
}

QList<Activity*> ActivityRepository::get(QList<QUuid> ids) {
    QList<Activity*> activities;
    for (auto &id : ids)
        activities.append(get(id));
    return activities;
}

QList<Activity*> ActivityRepository::get_all() {
    return container.values();
}

